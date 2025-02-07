/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:12:51 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:45 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_terminal_settings(struct termios *orig_termios)
{
	if (tcgetattr(STDIN_FILENO, orig_termios) == -1)
	{
		print_error("tcgetattr");
		exit(1);
	}
}

void	restore_terminal_settings(const struct termios *orig_termios)
{
	printf("Restoring terminal settings!\n");
	if (tcsetattr(STDIN_FILENO, TCSANOW, orig_termios) == -1)
	{
		print_error("tcsetattr");
		exit(1);
	}
	printf("Restored VQUIT: %d\n", orig_termios->c_cc[VQUIT]);
}
