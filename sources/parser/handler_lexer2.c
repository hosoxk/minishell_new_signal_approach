/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:56:36 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/06 11:01:29 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	add_quoted_token(char **line, char *quoted_str, char quote_char,
		t_token **token_list)
{
	if (quote_char == '\'')
	{
		if (!add_token_to_list(token_list, quoted_str, QUOTED_STRING))
			return (false);
	}
	else if (quote_char == '\"')
	{
		if (!add_token_to_list(token_list, quoted_str, DOUBLE_QUOTED_STRING))
			return (false);
	}
	else
	{
		if ((**line) == '\'')
		{
			if (!add_token_to_list(token_list, quoted_str, FAKE_QUOTED_STRING))
				return (false);
		}
		else if (!add_token_to_list(token_list, quoted_str,
				FAKE_DOUBLE_QUOTED_STRING))
			return (false);
	}
	free(quoted_str);
	(*line)++;
	return (true);
}

//(*(*line + 1) == '\0' || *(*line + 1) == ' ')
bool	handle_quoted_str(char **line, t_token **token_list,
		char *absoluut_begin)
{
	char	quote_char;
	char	*start;
	char	*quoted_str;

	if (!line || !token_list)
		return (print_error("null parameter found for handle_quoted_str"),
			false);
	quote_char = **line;
	(*line)++;
	start = *line;
	while (**line && **line != quote_char)
		(*line)++;
	if (**line != quote_char)
		return (print_error_exit_status("Error: unmatched quote", 258), false);
	quoted_str = ft_strndup(start, *line - start);
	if (!quoted_str)
		return (print_error_status("Error: failure malloc in \
			handle_quoted_str"),
			false);
	if ((absoluut_begin == start || *(start - 2) == ' '))
		return (add_quoted_token(line, quoted_str, quote_char, token_list));
	return (add_quoted_token(line, quoted_str, '?', token_list));
}

static bool	handle_heredoc_append(char **line, char *special,
		t_token **token_list)
{
	if ((**line == '<' && *(*line + 1) == '<'))
	{
		special[1] = '<';
		if (!add_token_to_list(token_list, special, HEREDOC))
			return (false);
		(*line) += 2;
	}
	else if ((**line == '>' && *(*line + 1) == '>'))
	{
		special[1] = '>';
		if (!add_token_to_list(token_list, special, APPEND))
			return (false);
		(*line) += 2;
	}
	else
		return (false);
	return (true);
}

static bool	handle_single_redirect(char **line, char *special,
		t_token **token_list)
{
	if (**line == '<')
	{
		if (!add_token_to_list(token_list, special, REDIRECT_IN))
			return (false);
		(*line)++;
	}
	else if (**line == '>')
	{
		if (!add_token_to_list(token_list, special, REDIRECT_OUT))
			return (false);
		(*line)++;
	}
	else
		return (false);
	return (true);
}

bool	handle_redirect(char **line, t_token **token_list)
{
	char	special[3];

	if (!line || !(*line))
		return (print_error("Handler received a null line pointer"), false);
	special[0] = **line;
	special[1] = '\0';
	special[2] = '\0';
	if (!handle_heredoc_append(line, special, token_list))
		if (!handle_single_redirect(line, special, token_list))
			return (false);
	return (true);
}
