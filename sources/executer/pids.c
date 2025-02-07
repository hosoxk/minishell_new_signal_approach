/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:07:07 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/07 15:53:44 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Calculates the number of WORD type nodes in an AST.
 * 
 * This function recursively traverses an abstract syntax tree (AST) 
 * and counts the number of nodes that are of type WORD. It returns 
 * the total count of such nodes in the tree.
 * 
 * @param ast_root The root of the AST to traverse.
 * @param len Unused parameter, reserved for future use.
 * @return The number of WORD type nodes in the AST.
 */
static int	get_len_ast(t_ast *ast_root, int len)
{
	int	i;

	if (!ast_root)
		return (0);
	if (ast_root->type == WORD)
		return (1);
	i = 0;
	i += get_len_ast(ast_root->left, len);
	i += get_len_ast(ast_root->right, len);
	return (i);
}

/**
 * @brief Get a list of process IDs for an AST.
 * 
 * This function allocates an array of pid_t and initializes it with the number
 * of WORD type nodes in the given abstract syntax tree (AST). It returns the
 * address of the first element of the array, or NULL if the allocation fails.
 * 
 * The size of the array is one more than the number of WORD type nodes in the
 * AST, so that the last element of the array can be set to 0 (which marks the
 * end of the array in C).
 * 
 * @param ast_root The root of the AST to traverse.
 * @return A pointer to the first element of an array of pid_t, or NULL on
 * failure.
 */
pid_t	*get_pid_list(t_ast *ast_root)
{
	pid_t	*pids;

	pids = ft_calloc(sizeof(pid_t), get_len_ast(ast_root, 0) + 1);
	if (!pids)
		return (NULL);
	return (pids);
}

/**
 * @brief Adds a process ID to the PID list.
 * 
 * This function iterates through the provided array of process IDs (PIDs)
 * and places the specified PID at the first available position (marked by 0).
 * 
 * @param pids An array of process IDs. It is assumed the array has enough space
 * to accommodate the new PID.
 * @param pid The process ID to be added to the array.
 */
void	set_pid(pid_t *pids, pid_t pid)
{
	int	i;

	i = 0;
	while (pids[i])
		i++;
	pids[i] = pid;
}

/**
 * @brief Gets the number of non-zero elements in the provided array of process
 * IDs.
 * 
 * This function iterates through the provided array of process IDs (PIDs) and
 * returns the number of non-zero elements in the array. The function assumes
 * that the array is terminated by a zero element (i.e., a sentinel value of 0).
 * The function does not check whether the array is long enough to accommodate
 * the requested number of elements.
 * 
 * @param pids An array of process IDs.
 * @return The number of non-zero elements in the array.
 */
int	get_len_pids(pid_t *pids)
{
	int	i;

	i = 0;
	while (pids[i])
		i++;
	return (i);
}
