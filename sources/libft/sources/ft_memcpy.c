/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:48:47 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/04/14 19:34:55 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_dest;
	unsigned char		*ptr_src;
	size_t				i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (ptr_dest == ptr_src)
		return (dest);
	if (ptr_dest < ptr_src && (ptr_dest + n) > ptr_src)
		ft_memmove(dest, src, n);
	else if (ptr_src < ptr_dest && (ptr_src + n) > ptr_dest)
		ft_memmove(dest, src, n);
	else
	{
		i = 0;
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}
