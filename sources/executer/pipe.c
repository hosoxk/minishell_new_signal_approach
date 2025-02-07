/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:58:20 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/08 11:44:17 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Handles the child process of the pipe.
 * Duplicates the original stdout and replaces it with the write end of the pipe.
 * Executes the left command of the pipe.
 * Replaces stdout with the original stdout.
 * @param ast_root The AST node of the pipe.
 * @param env The environment variables.
 * @param pids The process IDs.
 * @param p_fd The pipe.
 * @return true on success, false on failure.
 */
static bool	child_process(t_ast *ast_root, char ***env, pid_t *pids, int *p_fd)
{
	int		fd_out;
	bool	return_value;

	fd_out = dup(STDOUT_FILENO);
	add_fd(ast_root, fd_out);
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	return_value = execute(ast_root->left, env, pids, false);
	dup2(fd_out, STDOUT_FILENO);
	pop_fd(ast_root);
	return (return_value);
}

/**
 * Handles the parent process of the pipe.
 * Duplicates the original stdin and replaces it with the read end of the pipe.
 * Executes the right command of the pipe.
 * Replaces stdin with the original stdin.
 * @param ast_root The AST node of the pipe.
 * @param env The environment variables.
 * @param pids The process IDs.
 * @param p_fd The pipe.
 * @return true on success, false on failure.
 */
static bool	parent_process(t_ast *ast_root, char ***env, pid_t *pids, int *p_fd)
{
	int		fd_in;
	bool	return_value;

	fd_in = dup(STDIN_FILENO);
	add_fd(ast_root, fd_in);
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	return_value = execute(ast_root->right, env, pids, true);
	dup2(fd_in, STDIN_FILENO);
	pop_fd(ast_root);
	return (return_value);
}

/**
 * Handles a pipe command.
 * Creates a pipe and forks the process. The child process is responsible for
 * writing to the pipe and executing the left command of the pipe. The parent
 * process is responsible for reading from the pipe and executing the right 
 * command of the pipe.
 * @param ast_root The AST node of the pipe.
 * @param env The environment variables.
 * @param pids The process IDs.
 * @return true on success, false on failure.
 */
bool	do_pipe(t_ast *ast_root, char ***env, pid_t *pids)
{
	pid_t	pid;
	int		p_fd[2];
	bool	return_value;

	if (pipe(p_fd) == -1)
		return (print_error_status("pipe failed"), false);
	pid = fork();
	if (pid == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		return (print_error_status("fork failed"), false);
	}
	if (!pid)
		return_value = child_process(ast_root, env, pids, p_fd);
	else
	{
		set_pid(pids, pid);
		return_value = parent_process(ast_root, env, pids, p_fd);
	}
	return (return_value);
}
