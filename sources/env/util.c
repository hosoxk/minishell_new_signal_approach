/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:29:19 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/27 16:29:20 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Retrieve the value of an environment variable without the name.
 *
 * @details
 * This function takes the name of an environment variable and the environment
 * variables array and returns the value of the variable without the name.
 * If the variable is not found, returns NULL.
 *
 * @param name The name of the environment variable to find.
 * @param env The environment variables array.
 * @return The value of the variable without the name, or NULL if not found.
 */
char	*getenv_stript(char *name, char **env)
{
	int	i;

	i = getenv_index(name, env);
	if (i != -1)
		return (env[i] + ft_strlen(name) + 1);
	return (NULL);
}

/**
 * @brief Retrieve the value of an environment variable given its name and the
 *        environment array.
 *
 * @details
 * This function takes a token, an index, a length, and the environment variables
 * array and returns the value of the environment variable whose name is the
 * substring of the token's value from index to index + len.
 *
 * @param token The token whose value contains the name of the environment
 *              variable.
 * @param index The index of the first character of the environment variable name
 *              in the token's value.
 * @param len The length of the environment variable name.
 * @param env The environment variables array.
 * @return The value of the environment variable if found, or NULL otherwise.
 */
char	*get_env_value(t_token *token, int index, int len, char **env)
{
	char	*env_name;
	char	*env_value;

	env_name = ft_strndup(&token->value[index], len);
	if (!env_name)
		return (NULL);
	env_value = getenv_stript(env_name, env);
	free(env_name);
	return (env_value);
}
