/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:46:05 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/08 01:30:32 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_in_cmd(int sig)
{
	(void)sig;
	printf("\n");
}

void	handle_sigint_here(int sig)
{
	(void)sig;
	set_exit_status(130);
	rl_on_new_line();
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

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
 */
/*
static void	handle_sigquit(int sig)
{
	(void)sig;
	printf("SIGQUIT handler triggered (signal %d)\n", sig);
	set_flag(SIGQUIT_PRESSED);
	set_exit_status(130);
}
*/
static void	handle_sigint(int sig)
{
	(void)sig;
	printf("SIGINT handler triggered (signal %d)\n", sig);
	set_flag(SIGINT_PRESSED);
	set_exit_status(130);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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

/*	Get current terminal settings with tcgetattr,
 *	_POSIX_VDISABLE disables signal-generating control characters
 *	Apply new settings to terminal
 */

/*
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
		print_error("tcsetattr (disable)");
		exit(1);
	}
	term.c_cc[VQUIT] = orig_vquit;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		print_error("tcsetattr (restore)");
		exit(1);
	}
}
*/

/*	Handles signals SIGINT and SIGQUIT
 *	SIGQUIT gets ignored by the handler SIG_IGN
 *	Disables signals that come from keyboard
 */

bool	setup_signals(void)
{
//	signal(SIGINT, handle_sigint);
//	signal(SIGQUIT, handle_sigquit);

	struct sigaction	sa;

	printf(BOLD_RED"Signals being set up ..."RESET);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		print_error("Failed to handle SIGINT");
		return (false);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		print_error("Failed to ignore SIGQUIT");
		return (false);
	}
	disable_signal_chars();
	return (true);
}
