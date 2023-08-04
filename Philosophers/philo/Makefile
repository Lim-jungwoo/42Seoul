# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 13:53:27 by jlim              #+#    #+#              #
#    Updated: 2021/10/09 14:05:50 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c error_manager.c init.c\
	   utils.c launcher.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror

PTHREAD = -lpthread

INCLUDE = .

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(PTHREAD) -o $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re clean fclean all
