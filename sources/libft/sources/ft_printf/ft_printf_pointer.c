/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:27:54 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/23 15:31:11 by yde-rudd         ###   ########.fr       */
/*   Updated: 2024/07/11 17:18:16 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_printf_pointer(unsigned long nbr)
{
	int				length;
	unsigned long	address;

	address = (unsigned long)nbr;
	length = 0;
	if (nbr == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	length += write(1, "0x", 2);
	length += ft_printf_hexa_baselow(address);
	return (length);
}
