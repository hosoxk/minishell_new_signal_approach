/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:11:34 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/10/02 23:04:54 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_cpyarr(char **src)
{
	char	**dest;
	int		i;

	i = 0;
	while (src[i] != NULL)
		i++;
	dest = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (ft_freearr(dest), NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
