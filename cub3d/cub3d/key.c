/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:41:28 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 17:45:03 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

static void	key_update_arrow(t_info *info)
{
	double	old_dirx;
	double	old_planex;

	if (info->key_left_arrow)
		key_left(info);
	if (info->key_right_arrow)
	{
		old_dirx = info->dirx;
		info->dirx = info->dirx * cos(-info->rotspeed)
			- info->diry * sin(-info->rotspeed);
		info->diry = old_dirx * sin(-info->rotspeed)
			+ info->diry * cos(-info->rotspeed);
		old_planex = info->planex;
		info->planex = info->planex * cos(-info->rotspeed)
			- info->planey * sin(-info->rotspeed);
		info->planey = old_planex * sin(-info->rotspeed)
			+ info->planey * cos(-info->rotspeed);
	}
}

void	key_update(t_info *info)
{
	key_update_ws(info);
	key_update_ad(info);
	key_update_arrow(info);
}

int	key_press(int key, t_info *info)
{
	if (key == K_W)
		info->key_w = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_D)
		info->key_d = 1;
	else if (key == K_AR_L)
		info->key_left_arrow = 1;
	else if (key == K_AR_R)
		info->key_right_arrow = 1;
	return (0);
}

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		close_win(info);
	if (key == K_W)
		info->key_w = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_D)
		info->key_d = 0;
	else if (key == K_AR_L)
		info->key_left_arrow = 0;
	else if (key == K_AR_R)
		info->key_right_arrow = 0;
	return (0);
}

int	close_win(t_info *info)
{
	int_map_clear(info);
	texture_clear(info);
	char_texture_clear(info);
	char_f_color_clear(info);
	char_c_color_clear(info);
	exit(0);
}
