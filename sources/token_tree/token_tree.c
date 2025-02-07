/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:18:58 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/21 09:26:58 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Handles the creation of an operator node in the token tree.
 * Searches for the first OR or AND operator in the token list.
 * If an operator is found, it creates a new operator node and updates the tree.
 * The right subtree is built from tokens after the operator,
 * and the left subtree is built from tokens before the operator.
 * 
 * @param tree Pointer to the token tree where the operator node will be added.
 * @param token_list The list of tokens to search for operators.
 * @return true if an operator node was created, otherwise false.
 */
static bool	handle_operator(t_token_tree **tree, t_token *token_list)
{
	t_token	*operator_token;

	operator_token = find_operator(token_list, OR);
	if (!operator_token)
		operator_token = find_operator(token_list, AND);
	if (operator_token)
	{
		*tree = get_token_node(operator_token->type, NULL);
		if (!*tree)
		{
			g_exit_status = 1;
			return (true);
		}
		build_token_tree(&(*tree)->right, operator_token->next);
		build_token_tree(&(*tree)->left, split_before(token_list,
				operator_token));
		free_token(operator_token);
		return (true);
	}
	return (false);
}

/**
 * Frees a token tree and all its nodes.
 *
 * @param tree Pointer to the token tree to free.
 */
void	free_token_tree(t_token_tree *tree)
{
	if (!tree)
		return ;
	if (tree->right)
		free_token_tree(tree->right);
	if (tree->left)
		free_token_tree(tree->left);
	if (tree->token_list)
		free_token_list(&(tree->token_list));
	free(tree);
}

/**
 * Builds a token tree from a token list.
 * Handles the construction of an operator node in the token tree.
 * Searches for the first OR or AND operator in the token list.
 * If an operator is found, it creates a new operator node and updates the tree.
 * The right subtree is built from tokens after the operator,
 * and the left subtree is built from tokens before the operator.
 * If no operator is found, the subtree is built from the entire token list.
 *
 * @param tree Pointer to the token tree where the operator node will be added.
 * @param token_list The list of tokens to search for operators.
 */
void	build_token_tree(t_token_tree **tree, t_token *token_list)
{
	if (!token_list)
	{
		g_exit_status = 0;
		*tree = NULL;
		free_token_list(&token_list);
		return ;
	}
	if (handle_parentheses_tree(tree, token_list))
		return ;
	if (handle_operator(tree, token_list))
		return ;
	*tree = get_token_node(WORD, token_list);
}

/**
 * Executes a token tree.
 * If the tree is a command, it executes it.
 * If the tree is an AND or OR operator, it executes the left subtree
 * and if the exit status is 0 (for AND) or non-zero (for OR), it executes
 * the right subtree.
 * If the tree is null, it returns true.
 *
 * @param tree The token tree to execute.
 * @param env The environment variables.
 * @param root The root of the token tree.
 * @return true if the tree was executed successfully, otherwise false.
 */
bool	execute_token_tree(t_token_tree *tree, char ***env, t_token_tree *root)
{
	bool	result;

	result = true;
	if (!tree)
		return (true);
	if (tree->type == WORD)
		return (execute_sub_commands(tree, env, root));
	else if (tree->type == AND)
	{
		result = execute_token_tree(tree->left, env, root);
		if (g_exit_status == 0)
			result = execute_token_tree(tree->right, env, root);
	}
	else if (tree->type == OR)
	{
		result = execute_token_tree(tree->left, env, root);
		if (g_exit_status != 0)
			result = execute_token_tree(tree->right, env, root);
	}
	return (result);
}
