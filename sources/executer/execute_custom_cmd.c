/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_custom_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:00:31 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/07 11:29:47 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Execute a custom command (export, unset, cd)
 * @param ast_root
 * @param env
 * @return true if the command was executed successfully, false otherwise
 */
bool	execute_custom_cmd(t_ast *ast_root, char ***env)
{
	char	*name;

	if (!ast_root->args)
		return (false);
	if (ast_root->type != WORD)
		return (false);
	name = ast_root->args[0];
	if (ft_strcmp(name, "exit") == 0)
		return (my_exit_normal(env, ast_root));
	if (ft_strcmp(name, "export") == 0)
		export(env, ast_root->args);
	else if (ft_strcmp(name, "unset") == 0)
		unset(env, ast_root->args);
	else if (ft_strcmp(name, "cd") == 0)
		my_cd(env, ast_root->args);
	else
		return (false);
	return (true);
}

/**
 * @brief Execute a custom command that needs to be executed in a forked process
 * (echo, env, pwd)
 * @param argv The command line arguments.
 * @param env The environment variables.
 * @return true if the command was executed successfully, false otherwise
 */
bool	execute_custom_cmd_after_fork(char **argv, char ***env)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		my_echo(argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		my_env(*env, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(argv[0], "exit") == 0)
		my_exit(argv);
	else
		return (false);
	return (true);
}
