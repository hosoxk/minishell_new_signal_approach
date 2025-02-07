/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:17:02 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/17 15:17:04 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_strnlen(const char *str, size_t max_len)
{
	size_t	len;

	len = 0;
	while (len < max_len && str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*result;

	len = ft_strnlen(s, n);
	result = malloc(len + 1);
	if (result)
	{
		ft_memcpy(result, s, len);
		result[len] = '\0';
	}
	return (result);
}
