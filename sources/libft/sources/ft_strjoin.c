/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:13:58 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/02 13:34:04 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_len(char *str, va_list args)
{
	int		len;
	char	*curr;

	len = 0;
	curr = str;
	while (curr)
	{
		len += ft_strlen(curr);
		curr = va_arg(args, char *);
	}
	return (len);
}

char	*ft_strjoin_multiple(char *str, ...)
{
	char	*new;
	int		len;
	int		index;
	va_list	args;

	va_start(args, str);
	len = get_len(str, args);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
	{
		va_end(args);
		return (NULL);
	}
	va_start(args, str);
	index = 0;
	while (str)
	{
		while (*str)
			new[index++] = *str++;
		str = va_arg(args, char *);
	}
	va_end(args);
	new[index] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("Hello World!\n");
// 	char *str = ft_strjoin_multiple("Hello", " ", "World", "!");
// 	printf("%s\n", str);
// 	free(str);
// 	return (0);
// }