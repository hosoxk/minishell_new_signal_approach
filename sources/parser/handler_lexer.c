/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:20:34 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/08 01:07:26 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_parentheses(char **line, t_token **token_list)
{
	bool	return_val;

	if (**line == '(')
		return_val = add_token_to_list(token_list, NULL, PARENTHESES_OPEN);
	else
		return_val = add_token_to_list(token_list, NULL, PARENTHESES_CLOSE);
	if (return_val)
		(*line)++;
	return (return_val);
}

bool	handle_pipe(char **line, t_token **token_list)
{
	(*line)++;
	if (**line == '|')
	{
		(*line)++;
		return (add_token_to_list(token_list, NULL, OR));
	}
	else
		return (add_token_to_list(token_list, "|", PIPE));
}

bool	handle_ampersand(char **line, t_token **token_list)
{
	(*line)++;
	if (**line == '&')
	{
		(*line)++;
		return (add_token_to_list(token_list, NULL, AND));
	}
	print_error("Syntax error: unexpected error near &");
	set_exit_status(2);
	return (false);
}
