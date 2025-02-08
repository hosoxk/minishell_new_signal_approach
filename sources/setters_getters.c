/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:40:21 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/08 00:42:26 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	get_flag(unsigned int flag)
{
	(void)flag;
	return ((g_flags & EXIT_STATUS_MASK) >> 8);
}

void	set_flag(unsigned int flag)
{
	printf("Setting flag: 0x%X\n", flag);
	g_flags |= flag;
}

void	set_exit_status(int status)
{
	g_flags &= ~EXIT_STATUS_MASK;
	g_flags |= ((status & 0xFF) << 8);
}

int	get_exit_status(void)
{
	return ((g_flags & EXIT_STATUS_MASK) >> 8);
}

void	clear_flag(unsigned int flag)
{
	g_flags &= ~flag;
}
