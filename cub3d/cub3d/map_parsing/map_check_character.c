/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:50:23 by jlim              #+#    #+#             */
/*   Updated: 2022/03/08 16:50:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	nsew_check(t_info *info, char c)
{
	int		x;
	int		y;
	int		ret;

	y = 0;
	ret = 0;
	while (y < info->map_h)
	{
		x = 0;
		while (x < info->map_w)
		{
			if (info->world_map[y][x] == c - '0')
			{
				info->character = c;
				info->posx = y + 0.5;
				info->posy = x + 0.5;
				info->world_map[y][x] = 0;
				ret++;
			}
			x++;
		}
		y++;
	}
	return (ret);
}

static int	map_check_character2(t_info *info)
{
	if (nsew_check(info, 'N') == 1)
	{
		if (nsew_check(info, 'S') == 1 || nsew_check(info, 'E') == 1
			|| nsew_check(info, 'W') == 1)
			return (-1);
		info->flag.n_flag = 1;
	}
	if (nsew_check(info, 'S') == 1)
	{
		if (nsew_check(info, 'N') == 1 || nsew_check(info, 'E') == 1
			|| nsew_check(info, 'W') == 1)
			return (-1);
		info->flag.s_flag = 1;
	}
	return (0);
}

int	map_check_character(t_info *info)
{
	if (map_check_character2(info) == -1)
		return (-1);
	if (nsew_check(info, 'E') == 1)
	{
		if (nsew_check(info, 'S') == 1 || nsew_check(info, 'N') == 1
			|| nsew_check(info, 'W') == 1)
			return (-1);
		info->flag.e_flag = 1;
	}
	if (nsew_check(info, 'W') == 1)
	{
		if (nsew_check(info, 'S') == 1 || nsew_check(info, 'E') == 1
			|| nsew_check(info, 'N') == 1)
			return (-1);
		info->flag.w_flag = 1;
	}
	if (info->flag.n_flag || info->flag.s_flag
		|| info->flag.e_flag || info->flag.w_flag)
		return (0);
	return (-1);
}
