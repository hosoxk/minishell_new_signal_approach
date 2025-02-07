/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:06:20 by kvanden-          #+#    #+#             */
/*   Updated: 2024/12/30 17:35:03 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief The echo command prints its arguments to the standard output
 *        followed by a newline.
 *
 * @param argv The arguments given to the echo command.
 *
 * If the first argument is "-n", the trailing newline is not printed.
 */
void	my_echo(char **argv)
{
	int		i;
	bool	is_print_end;

	i = 1;
	is_print_end = true;
	if (ft_strcmp(argv[1], "-n") == 0)
	{
		is_print_end = false;
		i = 2;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (is_print_end)
		ft_putchar_fd('\n', 1);
}
