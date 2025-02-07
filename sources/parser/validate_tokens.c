/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:08:12 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:23:07 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_pipe(t_token *token, t_token *prev_token)
{
	bool	is_valid;

	is_valid = false;
	if (!prev_token)
		print_error("Syntax error: unexpected pipe at the beginning");
	else if (!token->next)
		print_error("Syntax error: invalid pipe sequence");
	else if (!token->next || token->next->type != WORD)
		print_error("Syntax error: missing command after pipe");
	else
		is_valid = true;
	if (!is_valid)
		set_exit_status(258);
	return (is_valid);
}

static bool	check_logic_operators(t_token *token, t_token *prev_token)
{
	bool	is_valid;

	is_valid = false;
	if (!prev_token)
		print_error("Syntax error: unexpected operator at the beginning");
	else if (!token->next || token->next->type == AND
		|| token->next->type == OR)
		print_error("Syntax error: invalid operator sequence");
	else if (!token->next || token->next->type != WORD)
		print_error("Syntax error: missing command after operator");
	else
		is_valid = true;
	if (!is_valid)
		set_exit_status(258);
	return (is_valid);
}

static bool	check_redir(t_token *token)
{
	if (!token->next || token->next->type != WORD)
	{
		set_exit_status(258);
		print_error("Syntax error: missing target for redirection");
		return (false);
	}
	return (true);
}

bool	validate_token_sequence(t_token *tokens)
{
	t_token	*prev_token;
	int		depth;
	bool	is_valid;

	is_valid = true;
	prev_token = NULL;
	depth = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			is_valid = check_pipe(tokens, prev_token);
		else if (tokens->type >= REDIRECT_IN && tokens->type <= HEREDOC)
			is_valid = check_redir(tokens);
		else if (tokens->type == AND || tokens->type == OR)
			is_valid = check_logic_operators(tokens, prev_token);
		if (!is_valid)
			return (false);
		if (tokens->type == PARENTHESES_OPEN)
			depth++;
		if (tokens->type == PARENTHESES_CLOSE)
			depth--;
		prev_token = tokens;
		tokens = tokens->next;
	}
	return (depth == 0);
}
