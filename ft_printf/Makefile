# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 13:20:08 by jlim              #+#    #+#              #
#    Updated: 2021/06/08 13:25:43 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c parse_arg.c\
	   check_spec.c check_info.c change_hex.c\
	   apply_char.c apply_num.c\
	   print_char.c print_num.c

LIBFT = libft

LIBFT_LIB = libft.a

INCS = .

OBJS = $(SRCS:.c=.o)

RM = rm -f

LIBC = ar rc

CC = gcc

CFLAGS = -Wall -Wextra -Werror

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INCS)

$(NAME) : $(OBJS)
	make all -C $(LIBFT)/
	cp ./$(LIBFT)/$(LIBFT_LIB) $(NAME)
	$(LIBC) $(NAME) $(OBJS)

all : $(NAME)

clean :
	$(RM) $(OBJS)
	make clean -C $(LIBFT)

fclean : clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)

re : fclean all

.PHONY : libft clean fclean all re
