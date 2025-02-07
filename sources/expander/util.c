/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:07:36 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/15 15:37:36 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Swap the values and types of two t_token structures.
 *
 * This function exchanges the 'value' and 'type' fields between
 * two t_token instances, effectively swapping their contents.
 *
 * @param a Pointer to the first t_token structure.
 * @param b Pointer to the second t_token structure.
 */
static void	swap(t_token *a, t_token *b)
{
	char			*tmp;
	t_token_type	tmp_type;

	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
	tmp_type = a->type;
	a->type = b->type;
	b->type = tmp_type;
}

/**
 * Sort a linked list of t_token structs alphabetically by the value field.
 * Uses bubble sort algorithm.
 * @param list The linked list to be sorted.
 */
void	sort_linkt_list(t_token *list)
{
	t_token	*current;
	t_token	*next;

	current = list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcasecmp(current->value, next->value) > 0)
			{
				swap(current, next);
			}
			next = next->next;
		}
		current = current->next;
	}
}
