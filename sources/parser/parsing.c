/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:12:13 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/20 14:29:02 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_redirection(t_token **tokens, t_parse_vars *vars)
{
	t_ast	*redir_node;

	redir_node = create_redirection_node(tokens);
	if (!redir_node)
		return (print_error_status("Error: failure creating redirection node")
			, false);
	if (vars->is_prefix)
	{
		if (!vars->current_command)
		{
			vars->current_command = create_ast_node(WORD);
			vars->left_node = vars->current_command;
		}
		attach_redirection_to_command(vars->current_command, redir_node, 1);
		vars->is_prefix = 0;
	}
	else
		attach_redirection_to_command(vars->current_command, redir_node, 0);
	return (true);
}

static bool	handle_word_token(t_token **tokens, t_parse_vars *vars)
{
	if (!vars->current_command || vars->current_command->type != WORD)
	{
		vars->current_command = create_command_node(vars->left_node, tokens,
				&vars->size, &vars->count);
		vars->left_node = vars->current_command;
	}
	else
	{
		add_argument(&vars->current_command->args, &vars->size, &vars->count,
			(*tokens)->value);
		*tokens = (*tokens)->next;
	}
	vars->is_prefix = 0;
	return (true);
}

static bool	process_token(t_token **tokens, t_parse_vars *vars)
{
	if ((*tokens)->type == PIPE)
		return (create_pipe_node(vars->left_node, tokens, vars));
	else if ((*tokens)->type >= REDIRECT_IN && (*tokens)->type <= HEREDOC)
		return (handle_redirection(tokens, vars));
	else if ((*tokens)->type == WORD)
		return (handle_word_token(tokens, vars));
	else
		*tokens = (*tokens)->next;
	return (true);
}

t_ast	*create_ast_node(t_token_type type)
{
	t_ast	*node;

	node = malloc(sizeof (t_ast));
	if (!node)
	{
		print_error_status("Error: failure mallocing space for new ast_node");
		return (NULL);
	}
	node->type = type;
	node->args = NULL;
	node->file = NULL;
	node->left = NULL;
	node->right = NULL;
	node->free_data = NULL;
	return (node);
}

/*	Abstract Syntax Tree: tree-like data structure.
 *	Each node represents an operation (pipe, redir, ...),
 *	command with its arguments, or connections (left and right children).
 *	Child nodes represent components or arguments of that construct.
 *	Left child: the "upstream" operation or command,
 *	meaning the input for the current node.
 *	Right child: the "downstream" operation or command,
 *	meaning what happens next.
 *
 *	Step 1) Initialize
 *		left_node tracks the subtree constructed so far.
 *	Step 2) Token iteration
 *		Each token is processed sequentially in this function.
 */
t_ast	*parse_ast(t_token **tokens)
{
	t_parse_vars	vars;

	ft_bzero(&vars, sizeof (vars));
	vars.is_prefix = true;
	while (*tokens)
	{
		if (!process_token(tokens, &vars))
			return (vars.left_node);
	}
	return (vars.left_node);
}
