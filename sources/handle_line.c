/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:30:26 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:46:15 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reads a line of input from the standard input using get_next_line,
 *        removes the trailing newline character, and returns the line.
 *
 * @return A pointer to the line read from standard input, or NULL if an error
 *         occurs or end-of-file is reached.
 */
static char	*get_shell_input(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

/**
 * @brief Constructs a shell prompt string based on the current working directory
 *        and the exit status of the last executed command.
 *
 * The function retrieves the current working directory from the environment
 * variable "PWD" and extracts the directory name to be included in the prompt.
 * Based on the global exit status, the prompt's color changes to indicate
 * whether the last command was successful. The prompt format is:
 * - "➜  <directory_name> $minishell: " (in red) if the exit status is not zero.
 * - "➜  <directory_name> $minishell " (in green) if the exit status is zero.
 *
 * @param env The environment variables array used to retrieve the "PWD".
 * @return A dynamically allocated string containing the prompt, or NULL if an
 *         error occurs during processing.
 */
static char	*get_prompt(char **env)
{
	char	*prompt;
	char	*phat;
	char	*last_slash;
	char	*dir_name;

	phat = getenv_stript("PWD", env);
	if (!phat)
		return (NULL);
	last_slash = ft_strrchr(phat, '/');
	if (!last_slash)
		last_slash = phat;
	dir_name = ft_substr(phat, 1 + (last_slash - phat), ft_strlen(last_slash
				+ 1));
	if (!dir_name)
		return (NULL);
	if (get_exit_status() != 0)
		prompt = ft_strjoin_multiple(BOLD_RED, "➜  ", BOLD_BLUE, dir_name,
				BOLD_MAGENTA, "$minishell: ", RESET, NULL);
	else
		prompt = ft_strjoin_multiple(BOLD_GREEN, "➜  ", BOLD_BLUE, dir_name,
				BOLD_MAGENTA, "$minishell: ", RESET, NULL);
	free(dir_name);
	if (!prompt)
		return (NULL);
	return (prompt);
}

/**
 * @brief Gets a line of input from the user. If STDIN is not a terminal, it
 * reads from STDIN. Otherwise, it gets a prompt from get_prompt, reads a line
 * using readline, adds the line to the history, saves the line to the history
 * file, and returns the line.
 *
 * @param env The environment variables.
 * @return The line read from the user.
 */
char	*get_line(char **env)
{
	char	*line;
	char	*promt;

	if (!isatty(STDIN_FILENO))
		return (get_shell_input());
	promt = get_prompt(env);
	if (!promt)
		return (print_error_status("Failure getting prompt"), NULL);
	line = readline(promt);
	free(promt);
	if (!line)
		return (print_error("Exit"), NULL);
	if (*line)
		add_history(line);
	return (line);
}
