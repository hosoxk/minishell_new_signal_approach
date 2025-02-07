/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:58:16 by kvanden-          #+#    #+#             */
/*   Updated: 2025/01/06 11:58:17 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strappend(char *str, char c)
{
	char	*new_str;
	size_t	len;

	new_str = NULL;
	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	if (str)
		ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
