/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:38:48 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/07 23:30:12 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind error: 
// << lol --> ctrl + C --> exits minishell, shouldnt.
volatile unsigned int	g_flags = 0;

static bool	check_input(int argc, char **envp, char **argv)
{
	if (argc != 1)
	{
		printf(BOLD_RED"Incorrect arguments: ");
		while (*(++argv))
			printf("%s ", *argv);
		printf("\n"RESET);
		return (print_error_status("Correct usage: ./<executable>"), false);
	}
	if (!envp)
		return (print_error_status("Failure locating envp"),
			false);
	return (true);
}

/*	Checks parameters when running ./minishell
 *	Checks if STDIN_FILENO is connected to the terminal and sets up signals
 *	Reads input and tokenizes it
 *	After tokenizing, parses the token_list
 *	Gets expanded and executed
 */

//	printf(BOLD_MAGENTA"\nAbstract Syntax Tree:\n"RESET);
//	print_ast(ast_root, 0);
//	printf(BOLD_MAGENTA"\noutput:\n"RESET);
//	print_tokens(&tree->token_list); //// 

bool	execute_token_list(t_token *token_list, char ***env)
{
	t_ast		*root;
	t_free_data	data;
	bool		success;

	if (!expander(token_list, *env))
	{
		free_token_list(&token_list);
		return (false);
	}
	set_exit_status(0);
	root = get_ast(token_list, &data);
	if (!root)
		return (true);
//	signal(SIGINT, handle_sigint_in_cmd);
	success = executor(root, env);
//	setup_signals();
	free_ast(root);
	return (success);
}

static bool	execute_line(char *line, char ***env)
{
	t_token			*token_list;

	token_list = NULL;
	if (!lexer(line, &token_list))
		return (free(line), free_token_list(&token_list),
			false);
	free(line);
	if (!validate_token_sequence(token_list))
	{
		free_token_list(&token_list);
		return (true);
	}
	return (execute_token_list(token_list, env));
}

static bool	setup_terminal_signals(char **env, struct termios *orig_termios)
{
	if (isatty(STDIN_FILENO))
		if (!setup_signals())
			return (ft_free_tab(env), rl_clear_history(),
				restore_terminal_settings(orig_termios), false);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			**env;
	struct termios	orig_termios;

	save_terminal_settings(&orig_termios);
	if (!check_input(argc, envp, argv))
		return (1);
	env = create_env(envp);
	if (!env)
		return (1);
	if (!setup_terminal_signals(env, &orig_termios))
		return (get_exit_status());
	while (1)
	{
		line = get_line(env);
		if (!line)
			return (ft_free_tab(env), rl_clear_history(),
				restore_terminal_settings(&orig_termios), get_exit_status());
		if (!execute_line(line, &env))
			if (get_exit_status() != 258)
				return (ft_free_tab(env),
					restore_terminal_settings(&orig_termios), get_exit_status());
	}
	restore_terminal_settings(&orig_termios);
	return (get_exit_status());
}
