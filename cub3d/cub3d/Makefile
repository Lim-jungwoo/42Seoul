NAME = cub3d
NAME_LIB = cub3d.a

LIBFT = ../libft
LIBFT_LIB = libft.a

MLX = ../minilibx_opengl_20191021
MLX_LIB = libmlx.a

SRCS = init.c key.c main.c\
	my_raycast.c texture.c\
	clear.c print.c error.c\
	./map_parsing/map_check_character.c ./map_parsing/map_check_nsew.c\
	./map_parsing/map_check.c ./map_parsing/map_check_wall.c ./map_parsing/map_check_wall2.c\
	./map_parsing/map.c ./map_parsing/parse.c ./map_parsing/color.c\
	./map_parsing/color_hex.c ./map_parsing/color_funct.c ./map_parsing/map_color_check.c\
	./map_parsing/map_check_identifier.c ./map_parsing/sub_map_check_nsew.c\
	./map_parsing/map_to_int.c\
	clear2.c init_malloc.c init2.c key_wasd.c my_raycast2.c

OBJS_DIR = ./OBJS
OBJS = $(SRCS:.c=.o)

LIBC = ar rc

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_CFLAGS = -framework OpenGL -framework AppKit

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/$(LIBFT_LIB) $(MLX)/$(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/$(LIBFT_LIB) $(MLX)/$(MLX_LIB) $(MLX_CFLAGS) -o $(NAME)

$(LIBFT)/$(LIBFT_LIB):
	make -C $(LIBFT) all

$(MLX)/$(MLX_LIB):
	make -C $(MLX) all

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean
	make -C $(MLX) clean

fclean: clean
	$(RM) $(NAME) $(NAME_LIB)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re