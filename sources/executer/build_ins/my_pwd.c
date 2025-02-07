/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:59:25 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/02 11:22:24 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Prints the current working directory.
 *
 * @details
 * Uses the getcwd() POSIX function to retrieve the current working directory.
 * If getcwd() fails, prints an error message using perror() with the string
 * "getcwd".
 */
void	my_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd");
	}
}

// void	my_pwd(char **env)
// {
// 	char	*pwd;

// 	pwd = getenv_stript("PWD", env);
// 	ft_putendl_fd(pwd, STDOUT_FILENO);
// }
