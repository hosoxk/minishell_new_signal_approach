/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:16:33 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/09/17 09:34:07 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_is_num_minmax(char *str)
{
	int			sign;
	int			i;
	long long	nbr;

	sign = 1;
	i = 0;
	nbr = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr * sign < -2147483647 - 1 || nbr * sign > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isint(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-')
	{
		if (str[++i] == '\0')
			return (0);
	}
	while (str[i] != '\0')
	{
		if (ft_is_num_minmax(str))
			return (0);
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}
