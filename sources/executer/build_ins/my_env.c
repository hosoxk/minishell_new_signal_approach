/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:47:19 by kvanden-          #+#    #+#             */
/*   Updated: 2024/12/30 17:34:55 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Prints the environment variables to the standard output.
 * 
 * @param env A NULL-terminated array of strings representing the environment
 *            variables. Each element in the array is a string of the format
 *            "KEY=VALUE". The function will print each non-"NULL" string on
 *            a new line.
 */
void	my_env(char **env, char **argv)
{
	if (ft_tab_len(argv) != 1)
		return (print_error("env: No such file or directory"));
	while (*env)
	{
		if (ft_strcmp(*env, "NULL") != 0)
			ft_putendl_fd(*env, 1);
		env++;
	}
}
