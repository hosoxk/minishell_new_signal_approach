/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:48:39 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/06 12:30:00 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	create_pipe_node(t_ast *left_node, t_token **tokens, t_parse_vars *vars)
{
	t_ast	*pipe_node;

	pipe_node = create_ast_node(PIPE);
	if (!pipe_node)
		return (print_error_status("Failed to allocate memory for PIPE node"),
			false);
	pipe_node->left = left_node;
	*tokens = (*tokens)->next;
	pipe_node->right = parse_ast(tokens);
	vars->left_node = pipe_node;
	return (true);
}

void	attach_redirection_to_command(t_ast *command, t_ast *redir,
	bool is_prefix)
{
	t_ast	*temp;

	if (!redir)
	{
		print_error("Error: redirection node is NULL");
		return ;
	}
	if (!command)
		command = create_ast_node(WORD);
	if (is_prefix)
	{
		redir->right = command->left;
		command->left = redir;
	}
	else
	{
		temp = command->left;
		while (temp && temp->right)
			temp = temp->right;
		if (temp)
			temp->right = redir;
		else
			command->left = redir;
	}
}

t_ast	*create_redirection_node(t_token **tokens)
{
	t_ast	*redir_node;

	if (!tokens || !(*tokens))
		return (print_error("Null token pointer in \
			create_redirection_node"), NULL);
	redir_node = create_ast_node((*tokens)->type);
	if (!redir_node)
		return (print_error_status("Failed to allocate memory for \
			REDIRECTION node"),
			NULL);
	*tokens = (*tokens)->next;
	if ((*tokens) && (*tokens)->type == WORD)
	{
		redir_node->file = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	else
		return (print_error("Missing file for redirection"), NULL);
	return (redir_node);
}

t_ast	*create_command_node(t_ast *command_node, t_token **tokens,
	int *size, int *count)
{
	t_ast	*node;

	if (command_node && command_node->type == WORD)
		node = command_node;
	else
		node = create_ast_node(WORD);
	add_argument(&node->args, size, count, (*tokens)->value);
	*tokens = (*tokens)->next;
	return (node);
}
