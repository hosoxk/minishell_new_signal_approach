/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:21:22 by kvanden-          #+#    #+#             */
/*   Updated: 2025/02/07 23:45:51 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**

	* @brief Allocates a new string and copies the value of
	a token into it with the substring from index to index
	+ len replaced with the value of env_value.
 *
 * @param token The token whose value is being copied.
 * @param index The index at which the substring should be replaced.
 * @param env_value The value to replace the substring with.
 * @param len The length of the substring to be replaced.
 * @return The new string with the replaced substring.
 */
static char	*make_new_value(t_token *token, int index, char *env_value, int len)
{
	char	*new_value;

	new_value = malloc(sizeof(char) * (ft_strlen(token->value) - len
				+ ft_strlen(env_value) + 1));
	if (!new_value)
		return (print_error_status("malloc failed"), NULL);
	ft_strlcpy(new_value, token->value, index + 1);
	ft_strcpy(new_value + index - 1, env_value);
	ft_strcpy(new_value + index - 1 + ft_strlen(env_value), &token->value[index
		+ len]);
	return (new_value);
}

/**
 * @brief Returns the length of a substring in a string that only contains
 *        alphanumeric characters, '_', '-', and '?'.
 *
 * @param str The string in which to find the substring.
 * @return The length of the substring.
 */
static int	find_length(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'
			|| str[len] == '-' || str[len] == '?' || str[len] == '*'))
		len++;
	return (len);
}

/**
 * @brief Inserts the value of an environment variable into a token.
 *
 * @param token The token into which to insert the environment variable.
 * @param index The index of the first character of the environment variable
 *              name in the token's value.
 * @param env The environment array.
 * @return true if the operation was successful, false otherwise.
 *
 * If the environment variable is not found, the token's value is not modified.
 * If the environment variable is '?', the exit status is inserted instead.
 */
static char	*get_new_var(t_token *token, int index, char **env)
{
	int		len;
	char	*env_value;
	char	*new_value;
	bool	free_env_value;

	len = find_length(&token->value[index]);
	env_value = get_env_value(token, index, len, env);
	free_env_value = false;
	if (!env_value && token->value[index] == '?')
	{
		free_env_value = true;
		env_value = ft_itoa(get_exit_status());
		if (!env_value)
			return (NULL);
	}
	else if (!env_value)
		env_value = "";
	new_value = make_new_value(token, index, env_value, len);
	if (!new_value)
		return (NULL);
	if (free_env_value)
		free(env_value);
	return (new_value);
}

static bool	replace_var(t_token *token, char **env, char *dollar)
{
	char	*new_var;
	int		index;

	index = dollar - token->value + 1;
	new_var = get_new_var(token, index, env);
	if (!new_var)
		return (false);
	free(token->value);
	token->value = new_var;
	return (true);
}

bool	expand_var(t_token *token, char **env)
{
	char	*dollar;
	bool	return_value;

	return_value = true;
	dollar = ft_strchr(token->value, '$');
	while (dollar)
	{
		return_value = replace_var(token, env, dollar);
		if (!return_value)
			return (false);
		dollar = ft_strchr(token->value, '$');
	}
	return (return_value);
}
