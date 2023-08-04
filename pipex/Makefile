# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 14:14:19 by jlim              #+#    #+#              #
#    Updated: 2021/06/30 14:24:15 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c print_error.c ft_utils.c\
	   ft_check.c ft_get_env.c ft_pipe.c ft_strsplit.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "\033[1;35;m[Linking] : " | tr -d '\n'
	$(CC) $(CFLAGS) -o $@ $^
	@echo "\033[1;32;m[Success]"

%.o : %.c
	@echo "\033[1;36;m[Compiliing $<] : " | tr -d '\n'
	$(CC) $(CFLAGS) -c $<

clean :
	@echo "\033[0;33;m[Cleaning] : " | tr -d '\n'
	rm -f $(OBJS)

fclean : clean
	@echo "\033[0;31;m[Deleting $(NAME)] : " | tr -d '\n'
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
