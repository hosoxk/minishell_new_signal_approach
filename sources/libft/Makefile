# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kvanden- <kvanden-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 18:01:07 by yde-rudd          #+#    #+#              #
#    Updated: 2024/12/30 18:53:03 by yde-rudd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
AR = ar rcs
RM = rm -fr
MAKEFLAGS += -s

SRC_DIR = ./sources
GNL_DIR = $(SRC_DIR)/get_next_line
PRINTF_DIR = $(SRC_DIR)/ft_printf

YELLOW = \033[1;33m
GREEN = \033[1;32m
RESET = \033[0m

SRC = $(SRC_DIR)/ft_isalpha.c \
	$(SRC_DIR)/ft_isdigit.c \
	$(SRC_DIR)/ft_isalnum.c \
	$(SRC_DIR)/ft_isascii.c \
	$(SRC_DIR)/ft_isprint.c \
	$(SRC_DIR)/ft_isint.c \
	$(SRC_DIR)/ft_strlen.c \
	$(SRC_DIR)/ft_strlen_map.c \
	$(SRC_DIR)/ft_memset.c \
	$(SRC_DIR)/ft_bzero.c \
	$(SRC_DIR)/ft_memcpy.c \
	$(SRC_DIR)/ft_memmove.c \
	$(SRC_DIR)/ft_strlcpy.c \
	$(SRC_DIR)/ft_strlcat.c \
	$(SRC_DIR)/ft_calloc.c \
	$(SRC_DIR)/ft_strdup.c \
	$(SRC_DIR)/ft_toupper.c \
	$(SRC_DIR)/ft_tolower.c \
	$(SRC_DIR)/ft_strchr.c \
	$(SRC_DIR)/ft_strcmp.c \
	$(SRC_DIR)/ft_strncmp.c \
	$(SRC_DIR)/ft_memchr.c \
	$(SRC_DIR)/ft_memcmp.c \
	$(SRC_DIR)/ft_strnstr.c \
	$(SRC_DIR)/ft_atoi.c \
	$(SRC_DIR)/ft_strrchr.c \
	$(SRC_DIR)/ft_substr.c \
	$(SRC_DIR)/ft_strjoin.c \
	$(SRC_DIR)/ft_strtrim.c \
	$(SRC_DIR)/ft_split.c \
	$(SRC_DIR)/ft_itoa.c \
	$(SRC_DIR)/ft_strmapi.c \
	$(SRC_DIR)/ft_striteri.c \
	$(SRC_DIR)/ft_putchar_fd.c \
	$(SRC_DIR)/ft_putstr_fd.c \
	$(SRC_DIR)/ft_putendl_fd.c \
	$(SRC_DIR)/ft_putnbr_fd.c \
	$(SRC_DIR)/ft_cpyarr.c \
	$(SRC_DIR)/ft_freearr.c \
	$(SRC_DIR)/ft_lstnew.c \
	$(SRC_DIR)/ft_lstadd_front.c \
	$(SRC_DIR)/ft_lstsize.c \
	$(SRC_DIR)/ft_lstlast.c \
	$(SRC_DIR)/ft_lstadd_back.c \
	$(SRC_DIR)/ft_lstdelone.c \
	$(SRC_DIR)/ft_lstclear.c \
	$(SRC_DIR)/ft_lstiter.c \
	$(SRC_DIR)/ft_lstmap.c \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_utils.c \
	$(SRC_DIR)/is_white_space.c \
	$(SRC_DIR)/ft_strndup.c \
	$(SRC_DIR)/ft_realloc.c \
	$(SRC_DIR)/ft_strcpy.c \
	$(SRC_DIR)/ft_free_tab.c \
	$(SRC_DIR)/ft_copy_tab.c \
	$(SRC_DIR)/ft_print_tab.c \
	$(SRC_DIR)/ft_strappend.c

PRINTF_SRC = $(PRINTF_DIR)/ft_printf.c \
			 $(PRINTF_DIR)/ft_printf_char.c \
			 $(PRINTF_DIR)/ft_printf_int.c \
			 $(PRINTF_DIR)/ft_printf_string.c \
			 $(PRINTF_DIR)/ft_printf_hexa.c \
			 $(PRINTF_DIR)/ft_printf_pointer.c \
			 $(PRINTF_DIR)/ft_printf_unsigned.c

OBJS = $(SRC:.c=.o) $(PRINTF_SRC:.c=.o)

.c.o:
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${AR} ${NAME} ${OBJS}

all: ${NAME}

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(PRINTF_DIR)

fclean: clean
	@echo "$(YELLOW)Removing $(NAME) library...$(RESET)"
	$(RM) $(NAME)
	@echo "$(GREEN)Library $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
