/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:30:17 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:45:10 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Clean up after heredoc.
 * Frees the line that was read.
 * Closes the write end of the pipe.
 * Duplicates the original stdin and stdout onto their respective fds.
 * Closes the original stdin and stdout.
 * @param p_fd The pipe.
 * @param line The line that was read.
 * @param fd_in The original stdin.
 * @param fd_out The original stdout.
 */
static void	cleanup_heredoc(int *p_fd, int fd_in, int fd_out)
{
	close(p_fd[1]);
	dup2(fd_out, STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close(fd_out);
}

/**
 * Set up file descriptors for heredoc.
 * Closes the read end of the pipe.
 * Duplicates the original stdin and stdout.
 * Duplicates the write end of the heredoc pipe onto stdout.
 * Duplicates the read end of the heredoc pipe onto stdin.
 * Closes the write and read ends of the heredoc pipe.
 * @param p_fd The pipe.
 * @param ast_root The AST node of the heredoc.
 * @param fd_in The original stdin.
 * @param fd_out The original stdout.
 */
static void	setup(int *p_fd, t_ast *ast_root, int *fd_in, int *fd_out)
{
//	signal(SIGINT, handle_sigint_here);
	close(p_fd[0]);
	*fd_in = dup(STDIN_FILENO);
	*fd_out = dup(STDOUT_FILENO);
	dup2(ast_root->free_data->fd_out, STDOUT_FILENO);
	dup2(ast_root->free_data->fd_in, STDIN_FILENO);
	close(ast_root->free_data->fd_out);
	close(ast_root->free_data->fd_in);
}

static void	sigint_handler(int sig)
{
	(void)sig;
//	disable_signal_chars();
}

/*
 * Handles the heredoc side of the pipe.
 * It reads lines from stdin and writes them to the pipe until it reads a line
 * that matches the heredoc delimiter.
 * Once it has finished writing, it closes the pipe and waits for the other
 * side to finish.
 * After that, it cleans up the heredoc and exits.
 * @param ast_root The AST node of the heredoc.
 * @param p_fd The pipe.
 * @param env The environment.
 * @param pids The pids.
 */
static void	here_doc_put_in(t_ast *ast_root, int *p_fd, char **env, pid_t *pids)
{
	char	*ret;
	int		fd_in;
	int		fd_out;

	setup(p_fd, ast_root, &fd_in, &fd_out);
	while (1)
	{
		ret = readline("> ");
		if (!ret)
		{
			if (get_exit_status() != 130)
				print_error_status("here-document is delimited by \
				end-of-file!");
			break ;
		}
		if (ft_strcmp(ret, ast_root->file) == 0)
		{
			free(ret);
			break ;
		}
		ft_putendl_fd(ret, p_fd[1]);
		free(ret);
	}
	cleanup_heredoc(p_fd, fd_in, fd_out);
	free(pids);
	exit_clean(ast_root, env, get_exit_status());
}

/**
 * Initializes and handles the heredoc process.
 * Creates a pipe and forks the process. The child process handles the input
 * for the heredoc by calling `here_doc_put_in`. The parent process sets up the
 * pipe for reading and waits for the child process to complete.
 * Updates the global exit status based on the child process' exit status.
 * @param ast_root The AST node of the heredoc.
 * @param env The environment variables.
 * @param pids The process IDs.
 * @return true on success, false on failure.
 */

bool	init_heredoc(t_ast *ast_root, char **env, pid_t *pids)
{
	int		p_fd[2];
	pid_t	pid;
	int		temp_exit_status;

	if (pipe(p_fd) == -1)
		return (false);
	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == -1)
		return (false);
	if (!pid)
		here_doc_put_in(ast_root, p_fd, env, pids);
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		close(p_fd[0]);
		waitpid(pid, &temp_exit_status, 0);
		if (WIFEXITED(temp_exit_status))
			set_exit_status(WEXITSTATUS(temp_exit_status));
		else if (WIFSIGNALED(temp_exit_status))
			set_exit_status(128 + WTERMSIG(temp_exit_status));
	}
	return (true);
//	signal(SIGINT, handle_sigint_in_cmd);
}
