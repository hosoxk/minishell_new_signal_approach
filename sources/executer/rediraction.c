/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:59:33 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:43:51 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Open a file according to the given mode, and return the file descriptor.
 * If the file could not be opened, print an error message and return -1.
 * Mode can be one of REDIRECT_IN, REDIRECT_OUT, or APPEND.
 * The file is created if it does not exist, and truncated if it does exist.
 * The permissions of the created file are 0666.
 */
int	open_file(char *file, t_token_type mode)
{
	int	ret;

	if (mode == REDIRECT_IN)
		ret = open(file, O_RDONLY, 0666);
	if (mode == REDIRECT_OUT)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (mode == APPEND)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (ret == -1)
	{
		set_exit_status(1);
		perror(file);
	}
	return (ret);
}

/**
 * Initialize a redirection by opening the file and duplicating the
 * correct file descriptor to the correct standard file descriptor.
 * If the file could not be opened, return false.
 * If the redirection is successful, return true.
 */
static bool	init_redirection(t_ast *ast_root)
{
	int	fd;

	fd = open_file(ast_root->file, ast_root->type);
	if (fd == -1)
		return (false);
	if (ast_root->type == REDIRECT_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

/**
 * Handle a redirection by executing the left side of the redirection.
 * This function saves the original stdin and stdout, and replaces them
 * with the file descriptors of the redirection file.
 * If the redirection is a heredoc, it calls init_heredoc to handle it.
 * If the redirection is a simple redirection, it calls init_redirection.
 * If the left side of the redirection can be executed, it calls execute
 * to execute it.
 * After executing the left side, it restores the original stdin and stdout.
 * @param ast_root The AST node of the redirection.
 * @param env The environment variables.
 * @param pids The process IDs.
 * @param is_first Whether this is the first command of a pipe.
 * @return true if the redirection was successful, false otherwise.
 */
bool	do_redirection(t_ast *ast_root, char ***env, pid_t *pids, bool is_first)
{
	int		fd_in;
	int		fd_out;
	bool	can_execute;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	add_fd(ast_root, fd_in);
	add_fd(ast_root, fd_out);
	if (ast_root->type == HEREDOC)
		can_execute = init_heredoc(ast_root, *env, pids);
	else
		can_execute = init_redirection(ast_root);
	if (can_execute && ast_root->left && get_exit_status() != 130)
		can_execute = execute(ast_root->left, env, pids, is_first);
	if (can_execute)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
	}
	pop_fd(ast_root);
	pop_fd(ast_root);
	return (true);
}
