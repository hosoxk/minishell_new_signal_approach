/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:12:50 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/15 10:55:00 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_token_list(t_token **token_list)
{
	t_token	*tmp;

	if (!token_list || !*token_list)
		return ;
	while (*token_list)
	{
		tmp = (*token_list)->next;
		free_token(*token_list);
		*token_list = tmp;
	}
	*token_list = NULL;
}

void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->free_data && node == node->free_data->root)
	{
		close(node->free_data->fd_in);
		close(node->free_data->fd_out);
		clear_fds(node->free_data->fds);
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->file)
		free(node->file);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

/*
void	free_env(char **env)
{
	char	*pt;

	pt = *env;
	while (*pt)
	{
		free(pt);
		pt++;
	}
	free(*env);
	*env = NULL;
}

void	free_program(t_token *token_list, t_ast *ast_root, char **env)
{
	if (token_list)
		free_token_list(&token_list);
	if (ast_root)
		free_ast(ast_root);
	if (env)
		free_env(env);
}
*/