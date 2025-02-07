/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:26:15 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/01/06 11:57:31 by kvanden-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../../libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*read_from_file(int fd, char *current_content);
char	*line_from_buffer(char *buffer);
char	*handle_line(char *line, char *buffer, int allocate_length);
char	*update_buffer(char *buffer);
char	*free_buffer(char *buffer, char *buf);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strchr(const char *string, int character);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elementCount, size_t elementSize);
size_t	ft_strlen(const char *str);

#endif // GET_NEXT_LINE_H
