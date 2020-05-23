# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uboumedj <uboumedj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/22 16:31:48 by uboumedj          #+#    #+#              #
#    Updated: 2019/10/05 16:32:59 by uboumedj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft

SRCS = srcs/main.c srcs/initialise_shell.c srcs/read_command.c srcs/utils.c \
		srcs/builtin_commands.c srcs/error.c srcs/path_commands.c \
		srcs/builtin_commands2.c srcs/utils2.c

INC = minishell.h

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@ $(CC) $(CFLAGS) -o $(NAME) $(SRCS) -Iinclude $(LIBFT)/libft.a
	@echo "\033[1;34mminishell\033[1;32m...compiled\t✓\033[0m"

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@echo "\033[1;34mminishell project\033[1;33m obj files removed\t\033[1;31m✓\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)
	@echo "\033[1;34mminishell project\033[1;33m files deleted\t\t\033[1;31m✓\033[0m"

re: fclean all
