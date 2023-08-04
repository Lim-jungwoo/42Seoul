/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:33:54 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 16:53:44 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

static void	init_key(t_info *info)
{
	info->key_a = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_left_arrow = 0;
	info->key_right_arrow = 0;
	info->key_esc = 0;
}

static void	init_texture(t_info *info)
{
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
	info->texture = NULL;
}

static void	init_color(t_info *info)
{
	info->f_color = 0;
	info->c_color = 0;
	info->color.f_color = NULL;
	info->color.f_color1 = NULL;
	info->color.f_hex_color1 = NULL;
	info->color.f_color2 = NULL;
	info->color.f_hex_color2 = NULL;
	info->color.f_color3 = NULL;
	info->color.f_hex_color3 = NULL;
	info->color.c_color = NULL;
	info->color.c_color1 = NULL;
	info->color.c_hex_color1 = NULL;
	info->color.c_color2 = NULL;
	info->color.c_hex_color2 = NULL;
	info->color.c_color3 = NULL;
	info->color.c_hex_color3 = NULL;
}

static void	init_buf(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	init_info(t_info *info)
{
	info->map = NULL;
	info->world_map = NULL;
	info->map_w = 0;
	info->map_h = 0;
	info->character = 0;
	init_flag(info);
	init_key(info);
	init_texture(info);
	init_color(info);
	info->mlx = mlx_init();
	info->win = NULL;
	info->movespeed = 0.05;
	info->rotspeed = 0.05;
	init_buf(info);
	return (malloc_init_texture(info));
}
