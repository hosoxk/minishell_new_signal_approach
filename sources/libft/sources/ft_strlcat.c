/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:18:38 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/04/24 22:32:24 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srcl;
	size_t	dstl;
	size_t	i;
	size_t	j;

	srcl = ft_strlen(src);
	if (!dst && size == 0)
		return (srcl);
	j = ft_strlen(dst);
	dstl = j;
	if (size <= dstl)
		return (size + srcl);
	i = 0;
	while (src[i] && (j + 1) < size)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srcl + dstl);
}
