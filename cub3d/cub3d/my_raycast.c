/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:44:06 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 17:42:10 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	floor_ceiling_cast(t_info *info)
{
	int	color;
	int	x;
	int	y;

	y = WIN_HEIGHT / 2;
	while (++y < WIN_HEIGHT)
	{
		x = 0;
		while (++x < WIN_WIDTH)
		{
			color = info->f_color;
			info->buf[y][x] = color;
			color = info->c_color;
			info->buf[WIN_HEIGHT - y - 1][x] = color;
		}
	}
}

void	check_texture(t_info *info)
{
	info->wall.wall_x -= floor(info->wall.wall_x);
	info->wall.texture_x = (int)(info->wall.wall_x * (double)TEXTURE_WIDTH);
	if (info->wall.side == 0 && info->wall.ray_dirx > 0)
		info->wall.texture_x = TEXTURE_WIDTH - info->wall.texture_x - 1;
	if (info->wall.side == 1 && info->wall.ray_diry < 0)
		info->wall.texture_x = TEXTURE_WIDTH - info->wall.texture_x - 1;
}

void	wall_cast(t_info *info)
{
	int	x;
	int	y;

	info->wall.map_x = (int)info->posx;
	info->wall.map_y = (int)info->posy;
	x = -1;
	while (++x < WIN_WIDTH)
	{
		init_cast(info, x);
		info->wall.step = 1.0 * TEXTURE_HEIGHT / info->wall.line_height;
		info->wall.texture_pos = (info->wall.draw_start - WIN_HEIGHT / 2
				+ info->wall.line_height / 2) * info->wall.step;
		y = info->wall.draw_start - 1;
		while (++y < info->wall.draw_end)
		{
			info->wall.texture_y = (int)info->wall.texture_pos
				& (TEXTURE_HEIGHT - 1);
			info->wall.texture_pos
				+= info->wall.step;
			info->wall.color = info->texture[info->wall.num_texture]
			[TEXTURE_HEIGHT * info->wall.texture_y + info->wall.texture_x];
			info->buf[y][x] = info->wall.color;
		}
	}
}
