# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 13:47:25 by jlim              #+#    #+#              #
#    Updated: 2021/06/24 21:06:40 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_LIB = so_long.a

LIBFT = libft
LIBFT_LIB = libft.a

MLX = minilibx_opengl_20191021
MLX_LIB = libmlx.a

SRCS = so_long.c parse.c play.c\
       check_map.c check_wall.c map.c\
       init_mlx.c move.c close_win.c

OBJS = $(SRCS:.c=.o)

LIBC = ar rc

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_CFLAGS = -framework OpenGL -framework AppKit

RM = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	$(LIBC) $(NAME_LIB) $(<:.c=.o)

$(NAME) : $(OBJS) $(LIBFT)/$(LIBFT_LIB) $(MLX)/$(MLX_LIB)
	$(CC) $(CFLAGS) $(NAME_LIB) $(LIBFT)/$(LIBFT_LIB) $(MLX)/$(MLX_LIB) $(MLX_CFLAGS) -o $(NAME)

$(LIBFT)/$(LIBFT_LIB) :
	make -C $(LIBFT) all

$(MLX)/$(MLX_LIB) :
	make -C $(MLX) all

all : $(NAME)

clean :
	$(RM) $(OBJS)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean : clean
	$(RM) $(NAME) $(NAME_LIB)
	make -C $(LIBFT) fclean

re : fclean all

.PHONY : all bonus clean fclean re
