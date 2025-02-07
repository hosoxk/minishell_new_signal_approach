/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:15:46 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/07 23:41:07 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(int exit_status)
{
	set_exit_status(exit_status);
}

void	print_error(char *str)
{
	ft_putstr_fd(BOLD_RED, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

void	print_error_status(char *str)
{
	print_error(str);
	set_exit_status(1);
}

void	print_error_exit_status(char *str, int exit_status)
{
	print_error(str);
	set_exit_status(exit_status);
}

bool	is_special_case(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"' || c == '('
		|| c == ')' || c == '&')
		return (true);
	return (false);
}

// void	print_tokens(t_token **token_list)
// {
// 	t_token	*current;

// 	current = *token_list;
// 	while (current)
// 	{
// 		printf(BOLD_BLUE "Token: %s, Type: %d\n" RESET, current->value,
// 			current->type);
// 		current = current->next;
// 	}
// 	ft_putendl_fd("", STDOUT_FILENO);
// }

/*
void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	for (int i = 0; i < depth; i++)
		printf("  ");
	printf("Node: ");
	switch (node->type)
	{
	case (PIPE):
		printf("PIPE\n");
		break ;
	case (REDIRECT_IN):
		printf("REDIRECT_IN, file: %s\n", node->file);
		break ;
	case (REDIRECT_OUT):
		printf("REDIRECT_OUT, file: %s\n", node->file);
		break ;
	case (APPEND):
		printf("APPEND, file: %s\n", node->file);
		break ;
	case (HEREDOC):
		printf("HEREDOC, file: %s\n", node->file);
		break ;
	case (WORD):
		printf("COMMAND, args: ");
		if (node->args)
		{
			for (int i = 0; node->args[i]; i++)
				printf("%s ", node->args[i]);
		}
		printf("\n");
		break ;
	default:
		printf("UNKNOWN\n");
		break ;
	}
	printf(BOLD_BLUE "\nPrinting left child\n" RESET);
	print_ast(node->left, depth + 1);
	printf(BOLD_BLUE "\nPrinting right child\n" RESET);
	print_ast(node->right, depth + 1);
}
*/
