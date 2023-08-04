/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_raycast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:24:59 by jlim              #+#    #+#             */
/*   Updated: 2022/04/07 16:31:23 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_RAYCAST_H
# define MY_RAYCAST_H

# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "error.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17

# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64
# define MAP_WIDTH	24
# define MAP_HEIGHT	24
# define WIN_WIDTH	600
# define WIN_HEIGHT	400

# define K_A 0
# define K_D 2
# define K_S 1
# define K_W 13
# define K_ESC 53
# define K_AR_L 123
# define K_AR_R 124

# define NUM_TEXTURE	4

typedef struct s_map	t_map;
struct	s_map
{
	char	*line;
	t_map	*next;
	t_map	*prev;
};

typedef struct s_flag	t_flag;
struct	s_flag
{
	int		no_flag;
	int		so_flag;
	int		we_flag;
	int		ea_flag;
	int		f_flag;
	int		c_flag;
	int		n_flag;
	int		s_flag;
	int		e_flag;
	int		w_flag;
};

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}	t_img;

typedef struct s_wall
{
	double	camerax;
	double	ray_dirx;
	double	ray_diry;
	int		map_x;
	int		map_y;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		num_texture;
	double	wall_x;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_pos;
	int		color;
}	t_wall;

typedef struct s_color
{
	char	*f_color;
	char	*f_color1;
	char	*f_hex_color1;
	char	*f_color2;
	char	*f_hex_color2;
	char	*f_color3;
	char	*f_hex_color3;
	char	*c_color;
	char	*c_color1;
	char	*c_hex_color1;
	char	*c_color2;
	char	*c_hex_color2;
	char	*c_color3;
	char	*c_hex_color3;
}	t_color;

typedef struct s_info
{
	t_wall			wall;
	t_map			*map;
	int				**world_map;
	int				map_w;
	int				map_h;
	char			character;
	t_flag			flag;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int				**texture;
	int				f_color;
	int				c_color;
	t_color			color;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	void			*mlx;
	void			*win;
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				key_left_arrow;
	int				key_right_arrow;
	int				key_esc;
	t_img			img;
	int				buf[WIN_HEIGHT][WIN_WIDTH];
	double			movespeed;
	double			rotspeed;
}				t_info;

void	key_update(t_info *info);
int		key_press(int key, t_info *info);
int		key_release(int key, t_info *info);
int		close_win(t_info *info);
void	key_update_ad(t_info *info);
void	key_update_ws(t_info *info);
void	key_left(t_info *info);
int		init_info(t_info *info);
void	init_dir(t_info *info);
void	init_flag(t_info *info);
int		malloc_texture(t_info *info);
int		malloc_init_texture(t_info *info);
int		load_texture(t_info *info);
void	floor_ceiling_cast(t_info *info);
void	wall_cast(t_info *info);
void	init_cast(t_info *info, int x);
void	check_ray_dir(t_info *info);
void	check_hit(t_info *info);
void	wall_draw(t_info *info);
void	check_texture(t_info *info);
int		get_next_line(const int fd, char **line);
int		add_line_to_map(char *line, t_map **map_ptr);
int		parse_gnl(t_map **map_ptr, const int fd);
int		parse_map(t_map **map_ptr, const char *map_file, t_info *info);
int		map_width(t_map **map_ptr);
int		map_height(t_map **map_ptr);
int		map_check(t_map **map_ptr, t_info *info);
int		map_check_empty(t_map **map_ptr);
int		map_to_int(t_info *info, t_map **map_ptr);
int		map_check_first_ch(t_map **map_ptr);
int		map_check_end_ch(t_map **map_ptr);
int		map_check_first_line(t_map **map_ptr);
int		map_check_end_line(t_map **map_ptr);
int		map_check_space(t_map **map_ptr);
int		map_check_wall_next(t_map **map_ptr);
int		map_check_wall_prev(t_map **map_ptr);
int		map_check_character(t_info *info);
int		map_check_nsew(t_map **map_ptr, t_flag *nsew_flag, t_info *info);
int		check_f(t_map **map_ptr, t_flag *nsew_flag, t_info *info);
int		check_c(t_map **map_ptr, t_flag *nsew_flag, t_info *info);
int		map_check_identifier(t_map **map_ptr, t_info *info);
char	*map_check_texture(t_map **map_ptr);
void	map_print(t_map **map_ptr);
void	map_print2(t_info *info);
void	map_clear(t_map **map_ptr);
void	int_map_clear(t_info *info);
void	texture_clear(t_info *info);
void	char_texture_clear(t_info *info);
void	char_f_color_clear(t_info *info);
void	char_c_color_clear(t_info *info);
int		error(int error_num);
int		error_2(int error_num);
int		parse_map_error(t_map **map, t_info *info);
int		load_texture_error(t_info *info);
int		map_check_f_color(char **texture, t_info *info);
int		map_check_c_color(char **texture, t_info *info);
int		map_f_color(t_info *info);
int		map_c_color(t_info *info);
char	*malloc_color(char *color, int *index);
int		check_comma_space(char *color, int *index);
char	*int_to_char_hex(int color);
int		char_hex_to_int(char *color);

#endif