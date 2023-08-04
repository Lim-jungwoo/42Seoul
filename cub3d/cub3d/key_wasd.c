/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wasd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:41:49 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 17:46:16 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	key_update_ws(t_info *info)
{
	if (info->key_w)
	{
		if (!info->world_map[(int)(info->posx + info->dirx
				* info->movespeed)][(int)(info->posy)])
			info->posx += info->dirx * info->movespeed;
		if (!info->world_map[(int)(info->posx)][(int)(info->posy
				+ info->diry * info->movespeed)])
			info->posy += info->diry * info->movespeed;
	}
	if (info->key_s)
	{
		if (!info->world_map[(int)(info->posx - info->dirx
				* info->movespeed)][(int)(info->posy)])
			info->posx -= info->dirx * info->movespeed;
		if (!info->world_map[(int)(info->posx)]
				[(int)(info->posy - info->diry * info->movespeed)])
			info->posy -= info->diry * info->movespeed;
	}
}

void	key_update_a(t_info *info)
{
	if (info->wall.ray_dirx < 0 && info->wall.ray_diry < 0)
	{
		if (!info->world_map[(int)(info->posx
				+ info->movespeed)][(int)(info->posy)])
			info->posx += info->movespeed;
	}
	else if (info->wall.ray_dirx < 0 && info->wall.ray_diry > 0)
	{
		if (!info->world_map[(int)(info->posx)]
				[(int)(info->posy - info->movespeed)])
			info->posy -= info->movespeed;
	}
	else if (info->wall.ray_dirx > 0 && info->wall.ray_diry < 0)
	{
		if (!info->world_map[(int)(info->posx)]
				[(int)(info->posy + info->movespeed)])
			info->posy += info->movespeed;
	}
	else if (info->wall.ray_dirx > 0 && info->wall.ray_diry > 0)
	{
		if (!info->world_map[(int)(info->posx
				- info->movespeed)][(int)(info->posy)])
			info->posx -= info->movespeed;
	}
}

void	key_update_d(t_info *info)
{
	if (info->wall.ray_dirx < 0 && info->wall.ray_diry < 0)
	{
		if (!info->world_map[(int)(info->posx - info->movespeed)]
				[(int)(info->posy)])
			info->posx -= info->movespeed;
	}
	else if (info->wall.ray_dirx < 0 && info->wall.ray_diry > 0)
	{
		if (!info->world_map[(int)(info->posx)]
				[(int)(info->posy + info->movespeed)])
			info->posy += info->movespeed;
	}
	else if (info->wall.ray_dirx > 0 && info->wall.ray_diry < 0)
	{
		if (!info->world_map[(int)(info->posx)]
				[(int)(info->posy - info->movespeed)])
			info->posy -= info->movespeed;
	}
	else if (info->wall.ray_dirx > 0 && info->wall.ray_diry > 0)
	{
		if (!info->world_map[(int)(info->posx + info->movespeed)]
				[(int)(info->posy)])
			info->posx += info->movespeed;
	}
}

void	key_update_ad(t_info *info)
{
	if (info->key_a)
		key_update_a(info);
	if (info->key_d)
		key_update_d(info);
}

void	key_left(t_info *info)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = info->dirx;
	info->dirx = info->dirx * cos(info->rotspeed)
		- info->diry * sin(info->rotspeed);
	info->diry = old_dirx * sin(info->rotspeed)
		+ info->diry * cos(info->rotspeed);
	old_planex = info->planex;
	info->planex = info->planex * cos(info->rotspeed)
		- info->planey * sin(info->rotspeed);
	info->planey = old_planex * sin(info->rotspeed)
		+ info->planey * cos(info->rotspeed);
}
