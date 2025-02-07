/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paran.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:48 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/27 16:29:48 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Finds the closing parenthesis for the given opening parenthesis.
 * @param open_paren The opening parenthesis.
 * @return The closing parenthesis, or NULL if no closing parenthesis is found.
 */
static t_token	*find_closing_parenthesis(t_token *open_paren)
{
	int		depth;
	t_token	*current;

	depth = 1;
	current = open_paren->next;
	while (current && depth > 0)
	{
		if (current->type == PARENTHESES_OPEN)
			depth++;
		else if (current->type == PARENTHESES_CLOSE)
			depth--;
		if (depth == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * Inserts a subtree into the token tree after a specified token.
 * Searches for the first AND or OR operator in the token list starting
 * from the specified position. If found, creates a new operator node and
 * attaches the current tree as the left child. Builds the right subtree
 * from the remaining tokens and updates the tree to point to the new
 * operator node.
 * 
 * @param tree Pointer to the root of the token tree.

	* @param after Pointer to the token after which the subtree 
	should be inserted.
 */
static void	insort_tree_after(t_token_tree **tree, t_token *after)
{
	t_token			*first_op;
	t_token_tree	*operator_node;
	t_token			*next_tokens;

	if (!after)
		return ;
	first_op = find_operator(after, OR);
	if (!first_op)
		first_op = find_operator(after, AND);
	if (first_op)
	{
		operator_node = get_token_node(first_op->type, NULL);
		operator_node->left = *tree;
		next_tokens = first_op->next;
		first_op->next = NULL;
		build_token_tree(&operator_node->right, next_tokens);
		*tree = operator_node;
		free_token(first_op);
	}
}

/**
 * Inserts a subtree into the token tree before a specified token.
 * Searches for the last AND or OR operator in the token list before the
 * specified position. If found, creates a new operator node and
 * attaches the subtree as the right child. The left subtree is built
 * from the tokens before the operator. If no operator is found, the
 * subtree is attached directly to the tree.
 * 
 * @param tree Pointer to the root of the token tree.
 * @param before Pointer to the token before the subtree should be inserted.
 * @param subtree The subtree to be inserted.
 */
static void	insort_tree_befor(t_token_tree **tree, t_token *before,
		t_token_tree *subtree)
{
	t_token			*last_op;
	t_token_tree	*operator_node;

	if (!before)
	{
		*tree = subtree;
		return ;
	}
	last_op = find_last_operator(before);
	if (last_op)
	{
		operator_node = get_token_node(last_op->type, NULL);
		build_token_tree(&operator_node->left, before);
		operator_node->right = subtree;
		*tree = operator_node;
	}
	else
		*tree = subtree;
}

/**
 * Divides a token list into three parts: the tokens before the first
 * open parenthesis, the tokens inside the parentheses, and the tokens
 * after the closing parenthesis.
 * @param token_list The token list to be divided.
 * @param before The tokens before the first open parenthesis.
 * @param inside The tokens inside the parentheses.
 * @param after The tokens after the closing parenthesis.
 * @return True if the token list is divided successfully, false otherwise.
 */
static bool	divade_token_list(t_token *token_list, t_token **before,
		t_token **inside, t_token **after)
{
	t_token	*open_paren;
	t_token	*close_paren;

	open_paren = find_operator(token_list, PARENTHESES_OPEN);
	if (!open_paren)
		return (false);
	close_paren = find_closing_parenthesis(open_paren);
	*after = close_paren->next;
	*inside = open_paren->next;
	*before = NULL;
	if (open_paren != token_list)
		*before = split_before(token_list, open_paren);
	*inside = split_before(*inside, close_paren);
	free_token(close_paren);
	free_token(open_paren);
	return (true);
}

/**
 * Handles the construction of a token tree with respect to parentheses.
 * Divides the token list into sections: before, inside, and after the
 * parentheses. Constructs a subtree from the tokens inside the parentheses
 * and inserts it into the main tree in appropriate positions based on the
 * tokens before and after the parentheses.
 *
 * @param tree Pointer to the root of the token tree to be constructed.
 * @param token_list The list of tokens to process.
 * @return True if the token tree is constructed successfully, false otherwise.
 */
bool	handle_parentheses_tree(t_token_tree **tree, t_token *token_list)
{
	t_token_tree	*subtree;
	t_token			*before;
	t_token			*inside;
	t_token			*after;

	if (!divade_token_list(token_list, &before, &inside, &after))
		return (false);
	subtree = NULL;
	build_token_tree(&subtree, inside);
	insort_tree_befor(tree, before, subtree);
	insort_tree_after(tree, after);
	return (true);
}
