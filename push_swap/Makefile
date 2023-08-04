# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/29 17:59:58 by jlim              #+#    #+#              #
#    Updated: 2021/09/30 12:36:39 by jlim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

NAME2 = push_swap

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB = ./libft/libft.a

LIB_PATH = ./libft

INCLUDES = -I libft/includes -I ./includes

SRC_PATH = ./srcs

OBJ_PATH = ./objs

SRC_NAME = 	checker.c 								\
			lst_func.c								\
			create_list.c							\
			check_arg.c								\
			push.c									\
			reverse_rotate.c						\
			rotate.c								\
			swap.c									\
			utils.c									\

SRC_NAME2 = push_swap.c								\
			resolve.c								\
			short_resolve.c							\
			lst_func.c								\
			create_list.c							\
			check_arg.c								\
			push.c									\
			find_median.c							\
			reverse_rotate.c						\
			rotate.c								\
			swap.c									\
			utils.c									\

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_NAME2 = $(SRC_NAME2:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

SRC2 = $(addprefix $(SRC_PATH)/, $(SRC_NAME2))

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

OBJ2 = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME2))

all: $(NAME) $(NAME2)

$(NAME): $(OBJ)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIB) -o $(NAME)
	@echo "\x1b[36m[CHECKER COMPILED]\x1b[0m"

$(NAME2): $(OBJ2)
	@make -C $(LIB_PATH)
	@$(CC) $(CFLAGS) $(OBJ2) $(INCLUDES) $(LIB) -o $(NAME2)
	@echo "\x1b[36m[PUSH_SWAP COMPILED]\x1b[0m"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@make clean -C $(LIB_PATH)
	@rm -rf $(OBJ)
	@rm -rf $(OBJ2)
	@rm -rf $(OBJ_PATH)
	@echo "\033[33mall $(NAME) and $(NAME2) .o files are removed\033[0m"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME) $(NAME2)
	@echo "\033[31m$(NAME) and $(NAME2) is deleted\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
