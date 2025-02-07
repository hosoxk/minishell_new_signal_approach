/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:12 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/27 16:29:13 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_new_env(int i, int size, char **env)
{
	char	*temp;

	if (i < size)
		temp = ft_strdup(env[i]);
	else
		temp = ft_strdup("NULL");
	return (temp);
}

char	**expent_env(char **env)
{
	int		size;
	int		i;
	char	**new_env;
	char	*temp;

	size = ft_tab_len(env);
	new_env = ft_calloc(size * 2, sizeof(char *));
	if (!new_env)
		return (print_error_status("malloc failed"), NULL);
	i = 0;
	while (i < ((size * 2) - 1))
	{
		temp = get_new_env(i, size, env);
		if (!temp)
		{
			new_env[i] = NULL;
			ft_free_tab(new_env);
			return (print_error_status("malloc failed"), NULL);
		}
		new_env[i] = temp;
		i++;
	}
	ft_free_tab(env);
	return (new_env);
}
