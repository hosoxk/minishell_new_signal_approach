/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:18:56 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:19:39 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	incroment_shell_level(char ***env)
{
	int		n;
	char	*org_number;
	char	*mod_number;

	org_number = getenv_stript("SHLVL", *env);
	if (!org_number)
		n = 1;
	else
		n = ft_atoi(org_number) + 1;
	mod_number = ft_itoa(n);
	if (!mod_number)
	{
		print_error_status("failure convorting shell level");
		return (false);
	}
	if (!update_env("SHLVL", mod_number, env))
	{
		free(mod_number);
		return (false);
	}
	free(mod_number);
	return (true);
}

static bool	set_pwd(char ***env)
{
	char	cwd[PATH_MAX];

	if (getenv_stript("PWD", *env))
		return (true);
	if (!getcwd(cwd, sizeof(cwd)))
	{
		set_exit_status(1);
		perror("getcwd");
		return (false);
	}
	return (update_env("PWD", cwd, env));
}

static bool	set_path(char ***env)
{
	if (getenv_stript("PATH", *env))
		return (true);
	return (update_env("PATH", "/bin:/usr/bin", env));
}

static bool add_exit_status(char ***env)
{
	return (update_env("?", "0", env));
}

char	**create_env(char **envp)
{
	char	**env;

	env = ft_copy_tab(envp);
	if (!env)
		return (print_error_status("Failure copying envp into env"), NULL);
	if (!add_exit_status(&env))
		return (ft_free_tab(env), NULL);
	if (!incroment_shell_level(&env))
		return (ft_free_tab(env), NULL);
	if (!set_pwd(&env))
		return (ft_free_tab(env), NULL);
	if (!set_path(&env))
		return (ft_free_tab(env), NULL);
	return (env);
}
