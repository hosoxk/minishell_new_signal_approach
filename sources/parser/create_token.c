/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:39:13 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/27 16:41:16 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*init_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof (t_token));
	if (!new_token)
		return (print_error_status("Failure mallocing space for new_token"),
			NULL);
	new_token->type = type;
	new_token->next = NULL;
	new_token->value = NULL;
	new_token->value = ft_strdup(value);
	if (!new_token->value && value)
		return (free(new_token), print_error("Error: "),
			print_error_status("failure ft_strdup in add_token_to_list"), NULL);
	return (new_token);
}

/*	Allocate space for a new t_token, if token_list is present,
 *	token iterates to the end of the list
 */

bool	add_token_to_list(t_token **token_list, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*current;

	if (!token_list)
		return (print_error("null parameter found for add_token_to_list"),
			false);
	current = NULL;
	new_token = init_token(value, type);
	if (!new_token)
		return (false);
	if (!*token_list)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
	return (true);
}
