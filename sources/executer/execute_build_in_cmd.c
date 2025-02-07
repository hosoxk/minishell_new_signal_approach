/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_build_in_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:00:45 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/06 18:22:09 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * @brief Searches for the full executable path of a command within the 
 * system's PATH environment variable.
 *
 * @details
 * This function splits the PATH environment variable into individual
 * directories, iterates through each directory, and constructs a potential
 * full path for the provided command. The constructed path is checked for 
 * existence and execution permissions. 
 * If a valid path is found, it is returned. 
 * Otherwise, the function returns NULL.
 *
 * @param cmd The command to search for in the system's PATH.
 * @param env The environment variables array used to retrieve the PATH variable.
 * @return A dynamically allocated string containing the full path to the
 * executable, or NULL if the executable is not found or is not accessible.
 */
static char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**all_paths;
	char	*path;

	i = -1;
	path = getenv_stript("PATH", env);
	if (!path)
		return (NULL);
	all_paths = ft_split(path, ':');
	while (all_paths && all_paths[++i])
	{
		exec = ft_strjoin_multiple(all_paths[i], "/", cmd, NULL);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(all_paths);
			return (exec);
		}
		ft_free((void **)&exec);
	}
	ft_free_tab(all_paths);
	return (NULL);
}

/**
 * @brief Execute a command by looking up its full path in the system's PATH
 * environment variable.
 *
 * @details
 * This function first looks up the full path of the given command by
 * splitting the PATH environment variable into individual directories,
 * iterating through each directory, and constructing a potential full path
 * for the provided command. If the constructed path is valid (i.e., the file
 * exists and has execution permissions), it is executed with the provided
 * command line arguments and environment variables.
 * If no valid path is found, the command is executed directly with the
 * provided command line arguments and environment variables.
 *
 * @param argv The command line arguments for the command to execute.
 * @param env The environment variables array used to retrieve the PATH
 * variable and to pass to the executed command.
 */

void	execute_build_in_cmd(char **argv, char **env)
{
	char	*path;
	char	*name;

	name = argv[0];
	if (!name)
	{
		ft_putendl_fd("pipex: command not found: ", STDERR_FILENO);
		exit(127);
	}
	path = get_path(name, env);
	signal(SIGQUIT, SIG_DFL);
	if (path)
	{
		execve(path, argv, env);
		free(path);
	}
	else
	{
		execve(name, argv, env);
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(name, STDERR_FILENO);
	}
}
