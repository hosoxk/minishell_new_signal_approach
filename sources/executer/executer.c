/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:32:53 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:29:27 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
* @brief Execute a command (only if it's not a built-in nor a redirection nor a
 * pipe).
 * @param ast_root The root of the AST.
 * @param env The environment variables.
 * @param pids An array of pids (not used).
 */
static void	do_cmd(t_ast *ast_root, char ***env, int *pids)
{
	free(pids);
	if (!ast_root->args || !ast_root->args[0])
	{
		exit_clean(ast_root, *env, 0);
		return ;
	}
	if (ft_strlen(ast_root->args[0]) != 0
		&& !execute_custom_cmd_after_fork(ast_root->args, env))
	{
		execute_build_in_cmd(ast_root->args, *env);
		perror(ast_root->args[0]);
		exit_clean(ast_root, *env, -1);
		return ;
	}
	exit_clean(ast_root, *env, 0);
}

/**
* @brief Execute a command (only if it's not a built-in nor a redirection nor a
 * pipe). If is_first is true,
fork a new process and execute the command in it.
 * Otherwise, execute the command in the current process.
 * @param ast_root The root of the AST.
 * @param env The environment variables.
 * @param pids An array of pids (not used).
 * @param is_first Whether to fork a new process or not.
 * @return true if the command was executed successfully, false otherwise.
 */
static bool	execute_cmd(t_ast *ast_root, char ***env, pid_t *pids,
		bool is_first)
{
	pid_t	pid;

	if (is_first)
	{
		pid = fork();
		printf("forking ...\n");
		if (pid == -1)
			return (print_error_status("fork failed"), false);
		set_pid(pids, pid);
		if (!pid)
			do_cmd(ast_root, env, pids);
	}
	else
		do_cmd(ast_root, env, pids);
	return (true);
}

/**
 * @brief Executes a command based on the type of AST node.
 * 
 * This function handles the execution of different command types represented
 * by the abstract syntax tree (AST). It determines the type of operation to 
 * perform (WORD, PIPE, REDIRECTION, HEREDOC) and calls the corresponding 
 * function to execute the command.
 * 
 * @param ast_root The root of the AST representing the command.
 * @param env The environment variables.
 * @param pids An array to store process IDs for forked processes.
 * @param is_first Indicates whether this is the first command in a sequence.
 * @return true if the command was executed successfully, false otherwise.
 */

bool	execute(t_ast *ast_root, char ***env, pid_t *pids, bool is_first)
{
	if (ast_root->type == WORD)
		return (execute_cmd(ast_root, env, pids, is_first));
	else if (ast_root->type == PIPE)
		return (do_pipe(ast_root, env, pids));
	else if (ast_root->type >= REDIRECT_IN && ast_root->type <= HEREDOC)
		return (do_redirection(ast_root, env, pids, is_first));
	return (print_error_status("syntax error"), false);
}

/**
 * @brief Collects the exit statuses of all processes in the pids array and
 *        returns the last one.
 *
 * @param pids An array of process IDs.
 * @return The last exit status collected.
 *
 * This function waits for all processes in the pids array to finish and
 * collects their exit statuses. If a process terminates normally, its exit
 * status is returned unchanged. If a process terminates due to a signal, the
 * exit status is set to the signal number plus 128.
 */
int	get_exit_code(pid_t *pids)
{
	int	status;
	int	i;
	int	len;

	status = get_exit_status();
	len = get_len_pids(pids);
	i = 0;
	while (i < len)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			perror("waitpid failed");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = WTERMSIG(status) + 128;
		i++;
	}
	free(pids);
	return (status);
}

/**
 * @brief Execute a command represented by an abstract syntax tree (AST).
 * 
 * This function is the main entry point for command execution. It checks if the
 * command is a custom command and executes it if it is. Otherwise,
 * it gets a list of process IDs for the command, executes the command,
 * gets the exit code of the last process, and returns true if the command was
 * executed successfully, false otherwise.
 * 
 * @param ast_root The root of the AST representing the command.
 * @param env The environment variables.
 * @return true if the command was executed successfully, false otherwise.
 */
bool	executor(t_ast *ast_root, char ***env)
{
	pid_t	*pids;

	if (execute_custom_cmd(ast_root, env))
		return (get_exit_status() == 0 || get_exit_status() == 1);
	pids = get_pid_list(ast_root);
	if (!pids)
	{
		print_error_status("fork failed");
		return (false);
	}
	if (!execute(ast_root, env, pids, true))
		return (free(pids), false);
	set_exit_status(get_exit_code(pids));
	return (true);
}
