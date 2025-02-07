/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:24:40 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/12/30 15:28:04 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return ((int)*s2);
	if (s2 == NULL)
		return ((int)*s1);
	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return ((int)*s2);
	if (s2 == NULL)
		return ((int)*s1);
	i = 0;
	while ((ft_toupper(s1[i]) == ft_toupper(s2[i])) && s1[i] && s2[i])
		i++;
	return (ft_toupper(s1[i]) - ft_toupper(s2[i]));
}
