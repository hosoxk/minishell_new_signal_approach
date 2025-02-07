/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:36:02 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/14 09:36:02 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Allocates a new token tree node and initializes its members.
 * 
 * @param type The type of the node (WORD, PIPE, AND, OR, etc.).
 * @param token_list The list of tokens associated with the node.
 * @return The newly allocated node or NULL if malloc failed.
 */
t_token_tree	*get_token_node(t_token_type type, t_token *token_list)
{
	t_token_tree	*node;

	node = malloc(sizeof(t_token_tree));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->token_list = token_list;
	node->type = type;
	return (node);
}

/**
 * Finds the first occurrence of a specific operator in a token list.
 * If the operator is a closing parenthesis, it will only be found if
 * it is outside of any parentheses.
 * If the operator is an opening parenthesis, it will be found even if
 * it is inside other parentheses.
 * @param token_list The list of tokens to search for the operator.
 * @param type The type of operator to search for.
 * @return The first occurrence of the operator, or NULL if none is found.
 */
t_token	*find_operator(t_token *token, t_token_type type)
{
	int	depth;

	depth = 0;
	while (token)
	{
		if (token->type == PARENTHESES_OPEN)
			depth++;
		if (token->type == PARENTHESES_CLOSE)
			depth--;
		if ((depth == 0 || type == PARENTHESES_OPEN) && token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/**
 * Splits a token list into two parts: the part before the target token and
 * the part from the target token onwards.
 * @param list The token list to split.
 * @param target The token after which the list should be split.
 * @return The first part of the split list (everything before the target token).
 */
t_token	*split_before(t_token *list, t_token *target)
{
	t_token	*current;

	current = list;
	while (current && current->next != target)
		current = current->next;
	if (current)
		current->next = NULL;
	return (list);
}

/**
 * Finds the last AND or OR operator in the token list.
 * Iterates through the given token list and updates the last_op
 * pointer whenever an AND or OR operator is found. Returns the last
 * operator found in the list, or NULL if none is found.
 * 
 * @param token_list The list of tokens to search for operators.
 * @return The last AND or OR operator in the token list, 
 * or NULL if none is found.
 */

t_token	*find_last_operator(t_token *token_list)
{
	t_token	*last_op;
	t_token	*current;

	last_op = NULL;
	current = token_list;
	while (current)
	{
		if (current->type == AND || current->type == OR)
			last_op = current;
		current = current->next;
	}
	return (last_op);
}
