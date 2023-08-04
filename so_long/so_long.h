/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 08:40:25 by jlim              #+#    #+#             */
/*   Updated: 2021/06/24 20:49:43 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "./minilibx_opengl_20191021/mlx.h"

# define ERR1	"number of argument error\n"
# define ERR2	"open failure\n"
# define ERR3	"gnl failure\n"
# define ERR4	"malloc failure\n"
# define ERR5	"close failure\n"
# define ERR6	"invalid map\n"
# define ERR7	"mlx error\n"
# define ERR8	"error to read xpm file\n"
# define ERR9	"debug test\n"

# define W_KEY		13
# define A_KEY		0
# define S_KEY		1
# define D_KEY		2
# define ESC_KEY	53
# define FONT_COLOR	0x000E3B81

typedef struct s_map	t_map;
struct			s_map
{
	char	*line;
	t_map	*next;
};

typedef struct s_mlx	t_mlx;
struct			s_mlx
{
	t_map	*map;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img_ptr;
	void	*sprit1_ptr;
	void	*sprit2_ptr;
	void	*sprit3_ptr;
	void	*sprit4_ptr;
	char	*img;
	char	*sprit1;
	char	*sprit2;
	char	*sprit3;
	char	*sprit4;
	int		size_square;
	int		width;
	int		height;
	int		size_line;
	int		bpp;
	int		endian;
	int		move_count;
};

int				parse(t_map **map_ptr, const char *map_file);

int				check_map(t_map **map_ptr);
int				check_wall(t_map *map);

int				play(t_map *map);

int				init_mlx(t_mlx *mlx, t_map *map);

int				close_win(t_mlx *mlx);
int				is_fish(t_map *map);

void			move_left(t_mlx *mlx);
void			move_right(t_mlx *mlx);
void			move_up(t_mlx *mlx);
void			move_down(t_mlx *mlx);

int				map_width(t_map *map);
int				map_height(t_map *map);
char			map_index(t_map *map, int width, int height);
void			map_clear(t_map **map_ptr);

#endif
