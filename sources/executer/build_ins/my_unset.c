/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:54:12 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/06 11:31:42 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Remove a variable from the environment.
 *
 * @details
 * This function takes the name of a variable as argument and removes it from
 * the environment. If the variable does not exist, no action is taken.
 *
 * @param env The environment variables array.
 * @param argv The command line arguments for the unset command.
 * @return Nothing.
 */
void	unset(char ***env, char **argv)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], argv[1], ft_strlen(argv[1])) == 0)
		{
			temp = ft_strdup("NULL");
			if (!temp)
				return (print_error_status("malloc failed"));
			free((*env)[i]);
			(*env)[i] = temp;
		}
		i++;
	}
}
