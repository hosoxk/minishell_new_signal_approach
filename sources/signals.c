/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:46:05 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/07 23:15:14 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_flags(void)
{
	if (get_flag(SIGINT_PRESSED))
	{
		printf("Sigint caught\n");
		clear_flag(SIGINT_PRESSED);
	}
	if (get_flag(SIGQUIT_PRESSED))
	{
		printf("Sigquit caught\n");
		clear_flag(SIGQUIT_PRESSED);
	}
}

/*	Process gets terminated -> exit status = 130
 *	Prints new line to terminal
 */

static void	handle_sigquit(int sig)
{
	(void)sig;
	set_flag(SIGQUIT_PRESSED);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	set_flag(SIGINT_PRESSED);
	set_exit_status(130);
}

/*	Get current terminal settings with tcgetattr,
 *	_POSIX_VDISABLE disables signal-generating control characters
 *	Apply new settings to terminal
 */

void	disable_signal_chars(void)
{
	struct termios	term;
	int				orig_vquit;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		print_error("tcgetattr");
		exit(1);
	}
	orig_vquit = term.c_cc[VQUIT];
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		print_error("tcsetattr");
		exit(1);
	}
	term.c_cc[VQUIT] = orig_vquit;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		print_error("tcsetattr");
		exit(1);
	}
}

/*	Handles signals SIGINT and SIGQUIT
 *	SIGQUIT gets ignored by the handler SIG_IGN
 *	Disables signals that come from keyboard
 */

bool	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	return (true);
}
