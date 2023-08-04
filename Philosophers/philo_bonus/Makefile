# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 14:52:07 by jlim              #+#    #+#              #
#    Updated: 2021/10/09 14:55:12 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c error_manager.c init.c\
	   utils.c launcher.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDE = .

PTHREAD = -lpthread

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(PTHREAD) $(FLAGS) -o $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(FLAGS) -I $(INCLUDE) -c $< -o $(<:.c=.o)

.PHONY : clean fclean re all
