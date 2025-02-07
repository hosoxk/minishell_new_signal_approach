/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:39:13 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/23 15:29:52 by yde-rudd         ###   ########.fr       */
/*   Updated: 2024/06/26 16:40:42 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int	ft_printf_int(int nbr)
{
	int				count;
	unsigned int	i;

	count = 0;
	if (nbr < 0)
	{
		count += ft_printf_char('-');
		i = -nbr;
	}
	else
		i = nbr;
	if (i <= 9)
		count += ft_printf_char(i + 48);
	else
	{
		count += ft_printf_int(i / 10);
		count += ft_printf_char(i % 10 + 48);
	}
	return (count);
}
