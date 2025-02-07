/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:56:42 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/08 15:05:37 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Cleans up resources and exits the program with the specified exit status.
 *
 * This function frees the abstract syntax tree (AST) and token tree associated
 * with the provided AST node. It also frees the environment variables table.
 * If an exit status other than -1 is provided, the function exits with that
 * status. If the status is -1, the function exits with an error-based status
 * code: 127 for file not found or bad file descriptor errors, 126 for permission
 * denied errors, or the current value of errno for other errors.
 *
 * @param node The root node of the AST to be freed.
 * @param env The array of environment variables to be freed.
 * @param exit_status The desired exit status; if -1, uses error-based status.
 */
void	exit_clean(t_ast *node, char **env, int exit_status)
{
	if (node)
		free_ast(node->free_data->root);
	if (env)
		ft_free_tab(env);
	if (exit_status != -1)
		exit(exit_status);
	if (errno == ENOENT || errno == EBADF)
		exit(127);
	if (errno == EACCES)
		exit(126);
	exit(errno);
}
