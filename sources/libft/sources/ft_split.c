/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 01:15:45 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/05/01 13:14:27 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_words(char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static void	ft_freemalloc(char **str, int a)
{
	while (a >= 0)
	{
		free(str[a]);
		a--;
	}
	free(str);
}

static int	ft_size(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		a;
	char	**str;

	i = 0;
	a = -1;
	str = ft_calloc(sizeof(char *), (ft_words(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (++a < ft_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		str[a] = ft_calloc(sizeof(char), (ft_size((char *)s + i, c) + 1));
		if (str[a] == NULL)
		{
			ft_freemalloc(str, a);
			return (NULL);
		}
		j = 0;
		while (s[i] && s[i] != c)
			str[a][j++] = s[i++];
	}
	return (str);
}
