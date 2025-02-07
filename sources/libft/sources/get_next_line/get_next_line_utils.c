/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:25:51 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/19 15:11:59 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*handle_line(char *line, char *buffer, int allocate_length)
{
	int	i;

	i = 0;
	line = (char *)malloc(sizeof(char) * allocate_length);
	if (!line)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		sizetotal;
// 	char	*newstr;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	sizetotal = ft_strlen(s1) + ft_strlen(s2);
// 	newstr = malloc(sizeof(char) * (sizetotal + 1));
// 	if (!newstr || !s1 || !s2)
// 		return (NULL);
// 	while (s1[i] != 0)
// 	{
// 		newstr[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != 0)
// 	{
// 		newstr[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	newstr[sizetotal] = 0;
// 	return (newstr);
// }

// char	*ft_strchr(const char *string, int character )
// {
// 	char	*str;

// 	str = (char *)string;
// 	while (*str != (char)character && *str != 0)
// 		str++;
// 	if (*str == (char)character)
// 		return (str);
// 	else
// 		return (NULL);
// }
