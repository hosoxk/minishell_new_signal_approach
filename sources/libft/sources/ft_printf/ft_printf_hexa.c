/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:29:13 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/23 15:29:17 by yde-rudd         ###   ########.fr       */
/*   Updated: 2024/06/26 14:26:02 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_hexa(unsigned long nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	if (nbr > 0)
		count += (ft_printf_string("0x") + ft_printf_hexa_baselow(nbr));
	return (count);
}

int	ft_printf_hexa_baselow(unsigned long int nbr)
{
	int		count;
	char	*hexa;

	count = 0;
	hexa = "0123456789abcdef";
	if (nbr >= 16)
		count += ft_printf_hexa_baselow(nbr / 16);
	count += ft_printf_char(hexa[nbr % 16]);
	return (count);
}

int	ft_printf_hexa_baseup(unsigned long int nbr)
{
	int		count;
	char	*hexa;

	count = 0;
	hexa = "0123456789ABCDEF";
	if (nbr >= 16)
		count += ft_printf_hexa_baseup(nbr / 16);
	count += ft_printf_char(hexa[nbr % 16]);
	return (count);
}
