/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:12:13 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/05 15:12:13 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**

* @brief Expands a token by replacing '*' with the result of wildcard expansion
 *        and replacing '$' with the value of the environment variable that
 *        follows.
 *
 * @param token The token to expand.
 * @param env The environment array.
 * @return true if the operation was successful, false otherwise.
 *
 * This function expands a token by replacing '*' with the result of wildcard
 * expansion and replacing '$' with the value of the environment variable that
 * follows. If the environment variable is not found, the token's value is not
 * modified. If the environment variable is '?', the exit status is inserted
 * instead. If the token contains no '*' or '$', the function returns true
 * without modifying the token.
 */
static bool	expend_token(t_token *token, char **env)
{
	if (ft_strchr(token->value, '*'))
		if (!expand_wildcard(token))
			return (false);
	return (expand_var(token, env));
}

/**
 * @brief Expands all tokens in a linked list of tokens, replacing '*' with the
 *        result of wildcard expansion and replacing '$' with the value of the
 *        environment variable that follows.
 *
 * @param token_list The linked list of tokens to expand.
 * @param env The environment array.
 * @return true if the operation was successful, false otherwise.
 *

* This function goes through a linked list of tokens and expands each token that
 * contains '*' or '$' characters. If the token contains '*', the function

* replaces it with the result of wildcard expansion. If the token contains '$',
 * the function replaces it with the value of the environment variable that
 * follows. If the environment variable is not found, the token's value is not
 * modified. If the token contains no '*' or '$', the function returns true
 * without modifying the token. The function also changes the type of the
 * tokens to WORD after expansion is done.
 */
static bool	_expander(t_token *token_list, char **env)
{
	while (token_list)
	{
		if (token_list->type >= WORD
			&& token_list->type <= FAKE_DOUBLE_QUOTED_STRING)
		{
			if (!expend_token(token_list, env))
				return (false);
			if (token_list->type >= WORD
				&& token_list->type <= DOUBLE_QUOTED_STRING)
				token_list->type = WORD;
		}
		else if (token_list->type == QUOTED_STRING)
			token_list->type = WORD;
		token_list = token_list->next;
	}
	return (true);
}

static bool	setup(t_token *token_list, char **env, t_token **token,
		t_token **previous)
{
	if (!_expander(token_list, env))
		return (false);
	*token = token_list;
	*previous = NULL;
	if (!*token)
		return (true);
	if ((*token)->type == FAKE_DOUBLE_QUOTED_STRING
		|| (*token)->type == FAKE_QUOTED_STRING)
	{
		(*token)->type = WORD;
		*previous = *token;
		*token = (*token)->next;
	}
	return (true);
}

static bool	marge(t_token **token, t_token **previous)
{
	char	*temp;

	temp = ft_strjoin((*previous)->value, (*token)->value);
	if (!temp)
		return (print_error_status("Error: failure malloc"),
			false);
	free((*previous)->value);
	free((*token)->value);
	(*previous)->value = temp;
	(*previous)->next = (*token)->next;
	free(*token);
	*token = *previous;
	(*token)->type = WORD;
	return (true);
}

bool	expander(t_token *token_list, char **env)
{
	t_token	*token;
	t_token	*previous;

	if (!setup(token_list, env, &token, &previous))
		return (false);
	while (token)
	{
		if (token->type == FAKE_QUOTED_STRING
			|| token->type == FAKE_DOUBLE_QUOTED_STRING)
			if (previous->type == WORD
				|| previous->type == QUOTED_STRING
				|| previous->type == DOUBLE_QUOTED_STRING)
				if (!marge(&token, &previous))
					return (false);
		previous = token;
		token = token->next;
	}
	return (true);
}
