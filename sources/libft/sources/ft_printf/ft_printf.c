/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 00:39:02 by yde-rudd          #+#    #+#             */
/*   Updated: 2024/07/23 15:28:02 by yde-rudd         ###   ########.fr       */
/*   Updated: 2024/07/10 14:47:27 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	converse(char format, va_list list)
{
	int		count;

	count = 0;
	if (format == 'c')
		count = ft_printf_char(va_arg(list, int));
	else if (format == 's')
		count = ft_printf_string(va_arg(list, char *));
	else if (format == 'p')
		count = ft_printf_hexa(va_arg(list, unsigned long));
	else if (format == 'd' || format == 'i')
		count = ft_printf_int(va_arg(list, int));
	else if (format == 'u')
		count = ft_printf_unsigned(va_arg(list, unsigned int));
	else if (format == 'x')
		count = ft_printf_hexa_baselow(va_arg(list, unsigned int));
	else if (format == 'X')
		count = ft_printf_hexa_baseup(va_arg(list, unsigned int));
	else if (format == '%')
		count = ft_printf_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	size_t	i;
	size_t	chars_printed;

	if (!format)
		return (0);
	va_start(arg, format);
	i = 0;
	chars_printed = 0;
	while (format[i])
	{
		if (format[i] == '%')
			chars_printed += converse((char)format[++i], arg);
		else
		{
			write(1, &format[i], 1);
			chars_printed++;
		}
		i++;
	}
	va_end(arg);
	return (chars_printed);
}
