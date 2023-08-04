/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_raycast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:45:18 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 17:42:06 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	init_cast(t_info *info, int x)
{
	info->wall.camerax = 2 * x / (double)WIN_WIDTH - 1;
	info->wall.ray_dirx = info->dirx + info->planex * info->wall.camerax;
	info->wall.ray_diry = info->diry + info->planey * info->wall.camerax;
	info->wall.map_x = (int)info->posx;
	info->wall.map_y = (int)info->posy;
	info->wall.deltadistx = fabs(1 / info->wall.ray_dirx);
	info->wall.deltadisty = fabs(1 / info->wall.ray_diry);
	info->wall.hit = 0;
	check_ray_dir(info);
	check_hit(info);
	wall_draw(info);
	check_texture(info);
}

void	check_ray_dir(t_info *info)
{		
	if (info->wall.ray_dirx < 0)
	{
		info->wall.stepx = -1;
		info->wall.sidedistx = (info->posx - info->wall.map_x)
			* info->wall.deltadistx;
	}
	else
	{
		info->wall.stepx = 1;
		info->wall.sidedistx = (info->wall.map_x
				+ 1.0 - info->posx) * info->wall.deltadistx;
	}
	if (info->wall.ray_diry < 0)
	{
		info->wall.stepy = -1;
		info->wall.sidedisty = (info->posy
				- info->wall.map_y) * info->wall.deltadisty;
	}
	else
	{
		info->wall.stepy = 1;
		info->wall.sidedisty = (info->wall.map_y
				+ 1.0 - info->posy) * info->wall.deltadisty;
	}
}

void	check_hit(t_info *info)
{
	while (info->wall.hit == 0)
	{
		if (info->wall.sidedistx < info->wall.sidedisty)
		{
			info->wall.sidedistx += info->wall.deltadistx;
			info->wall.map_x += info->wall.stepx;
			info->wall.side = 0;
		}
		else
		{
			info->wall.sidedisty += info->wall.deltadisty;
			info->wall.map_y += info->wall.stepy;
			info->wall.side = 1;
		}
		if (info->world_map[info->wall.map_x][info->wall.map_y] > 0)
			info->wall.hit = 1;
	}
}

void	wall_draw_check(t_info *info)
{
	if (info->wall.side)
	{
		if (info->wall.ray_diry < 0)
			info->wall.num_texture = 2;
		else
			info->wall.num_texture = 3;
	}
	else
	{
		if (info->wall.ray_dirx < 0)
			info->wall.num_texture = 0;
		else
			info->wall.num_texture = 1;
	}
}

void	wall_draw(t_info *info)
{
	if (info->wall.side == 0)
		info->wall.perpwalldist = (info->wall.map_x - info->posx
				+ (1 - info->wall.stepx) / 2) / info->wall.ray_dirx;
	else
		info->wall.perpwalldist = (info->wall.map_y - info->posy
				+ (1 - info->wall.stepy) / 2) / info->wall.ray_diry;
	info->wall.line_height = (int)(WIN_HEIGHT / info->wall.perpwalldist);
	info->wall.draw_start = -info->wall.line_height / 2 + WIN_HEIGHT / 2;
	if (info->wall.draw_start < 0)
		info->wall.draw_start = 0;
	info->wall.draw_end = info->wall.line_height / 2 + WIN_HEIGHT / 2;
	if (info->wall.draw_end >= WIN_HEIGHT)
		info->wall.draw_end = WIN_HEIGHT - 1;
	wall_draw_check(info);
	if (info->wall.side == 0)
		info->wall.wall_x = info->posy + info->wall.perpwalldist
			* info->wall.ray_diry;
	else
		info->wall.wall_x = info->posx + info->wall.perpwalldist
			* info->wall.ray_dirx;
}
