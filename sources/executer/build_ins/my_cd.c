/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:25:13 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:42:12 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Construct a new directory path based on the given arguments.
 *
 * @details
 * If no arguments are provided, retrieves the HOME directory from the
 * environment variables and constructs a string with its path.
 * If the argument is '..', removes the last directory from the current working
 * directory.
 * If the argument is '.', uses the current working directory.
 * If the argument is an absolute path, constructs a new string with the given
 * path.
 * If the argument is a relative path, constructs a new string by joining the
 * current working directory with the given path.
 *
 * @param cwd The current working directory.
 * @param env The environment variables array.
 * @param argv The command line arguments for the cd command.
 * @return A dynamically allocated string containing the new directory path, or
 *         NULL if an error occurs during processing.
 */
static char	*get_new_dir(char *cwd, char **env, char **argv)
{
	char	*nwd;

	nwd = NULL;
	if (ft_tab_len(argv) > 2)
		return (print_error("cd: too many arguments"), NULL);
	if (argv[1] == NULL)
		nwd = ft_strdup(getenv_stript("HOME", env));
	else if (ft_strcmp(argv[1], ".") == 0)
		nwd = ft_strdup(cwd);
	else if (argv[1][0] == '/')
		nwd = ft_strdup(argv[1]);
	else if (ft_strcmp(argv[1], "..") == 0)
		nwd = ft_substr(cwd, 0, ft_strrchr(cwd, '/') - cwd);
	else
		nwd = ft_strjoin_multiple(cwd, "/", argv[1], NULL);
	if (!nwd)
		print_error_status("malloc failed");
	return (nwd);
}

/**
 * Changes the current working directory based on the given arguments.
 * If no arguments are provided, changes to the HOME directory.
 * If an error occurs in retrieving or changing the directory, sets
 * the global exit status and prints an error message.
 *
 * @param env The environment variables as an array of strings.
 * @param argv The command line arguments for the cd command.
 */
void	my_cd(char ***env, char **argv)
{
	char	cwd[PATH_MAX];
	char	*nwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (set_exit_status(1), perror("getcwd"));
	nwd = get_new_dir(cwd, *env, argv);
	if (!nwd)
	{
		set_exit_status(1);
		return ;
	}
	if (chdir(nwd) != 0)
	{
		perror(argv[1]);
		free(nwd);
		return ;
	}
	free(nwd);
	if (!getcwd(cwd, sizeof(cwd)))
		return (set_exit_status(1), perror("getcwd"));
	update_env("PWD", cwd, env);
}
