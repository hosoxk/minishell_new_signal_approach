/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:06:39 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/23 15:32:04 by yde-rudd         ###   ########.fr       */
/*   Updated: 2024/06/26 16:43:57 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_unsigned(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 9)
		count += ft_printf_char(nbr + 48);
	else
	{
		count += ft_printf_unsigned(nbr / 10);
		count += ft_printf_char(nbr % 10 + 48);
	}
	return (count);
}
