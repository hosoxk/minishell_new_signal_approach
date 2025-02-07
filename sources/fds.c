/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:23:13 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/15 15:54:15 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculates the number of pipes and redirections in an AST.
 * 
 * This function recursively traverses an abstract syntax tree (AST) 
 * and counts the number of nodes that are either pipes (PIPE) or 
 * redirections (REDIRECT_IN, REDIRECT_OUT, APPEND, HEREDOC). It 
 * returns the total count of such nodes in the tree.
 * 
 * @param tree The root of the AST to traverse.
 * @return The number of pipes and redirections in the tree.
 */
static int	get_len(t_ast *tree)
{
	int	i;

	i = 0;
	if (!tree)
		return (0);
	if (tree->type == PIPE)
		i = 2;
	else if (tree->type == HEREDOC)
		i = 3;
	else if (tree->type >= REDIRECT_IN && tree->type <= APPEND)
		i = 3;
	i += get_len(tree->left);
	i += get_len(tree->right);
	return (i);
}

/**
 * @brief Allocates and initializes an array of file descriptors.
 * 
 * This function calculates the number of pipes and redirections in 
 * the given abstract syntax tree (AST) and allocates an array of 
 * integers to hold file descriptors for these. The allocated array 
 * is initialized with -1 to indicate unused file descriptors.
 * 
 * @param tree The root of the AST to calculate pipes and redirections.
 * @return A pointer to the allocated and initialized array of file 
 * descriptors, or NULL if memory allocation fails.
 */
int	*get_fds(t_ast *tree)
{
	int	len;
	int	*fds;

	len = get_len(tree);
	if (len == 0)
		len = 1;
	fds = malloc(sizeof(int) * len);
	if (!fds)
		return (NULL);
	ft_memset(fds, -1, sizeof(int) * len);
	return (fds);
}

/**
 * @brief Closes all file descriptors in the given array and frees it.
 * 
 * This function iterates over the given array of file descriptors, 
 * closes each of them, and then frees the array. It does nothing if 
 * the input is NULL.
 */
void	clear_fds(int *fds)
{
	int	*pt;

	if (!fds)
		return ;
	pt = fds;
	while (*pt != -1)
	{
		close(*pt);
		pt++;
	}
	free(fds);
}

/**
 * @brief Adds a file descriptor to the array of file descriptors stored in 
 * the given AST's free_data.
 * 
 * This function adds a file descriptor to the array of file descriptors 
 * stored in the given abstract syntax tree (AST) node's free_data 
 * structure. It does nothing if the array of file descriptors in the free_data 
 * does not exist.
 * 
 * @param tree The AST node whose free_data should be modified.
 * @param fd The file descriptor to add.
 */
void	add_fd(t_ast *tree, int fd)
{
	int	*fds;

	if (!tree->free_data->fds)
		return ;
	fds = tree->free_data->fds;
	while (*fds != -1)
		fds++;
	*fds = fd;
}

/**
 * @brief Pops the last file descriptor from the array of file descriptors
 * stored in the given AST's free_data.
 * 
 * This function removes the last file descriptor from the array of
 * file descriptors stored in the given abstract syntax tree (AST) node's 
 * free_data structure. It does nothing if the array of file descriptors
 * in the free_data does not exist or is empty.
 * 
 * @param tree The AST node whose free_data should be modified.
 */
void	pop_fd(t_ast *tree)
{
	int	*fds;

	fds = tree->free_data->fds;
	if (!fds)
		return ;
	while (*fds != -1)
		fds++;
	fds--;
	close(*fds);
	*fds = -1;
}
