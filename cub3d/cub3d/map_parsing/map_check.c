/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:35:21 by jlim              #+#    #+#             */
/*   Updated: 2022/03/08 13:35:22 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	base_map_check(t_map **map_ptr)
{
	t_map	*check;
	int		line_number;
	int		index;

	check = *map_ptr;
	line_number = 0;
	index = 0;
	while (check->next)
	{
		line_number++;
		check = check->next;
	}
	if (line_number < 2)
		return (-1);
	return (0);
}

int	map_check_empty(t_map **map_ptr)
{
	while (ft_strcmp((*map_ptr)->line, "") == 0)
	{
		if ((*map_ptr)->next)
			(*map_ptr) = (*map_ptr)->next;
		else
			return (error(MAP_EMPTY));
	}
	return (0);
}

int	map_check_wall(t_map **check)
{
	if (base_map_check(check) == -1)
		return (-1);
	if (map_check_first_line(check) == -1)
		return (-1);
	if (map_check_end_line(check) == -1)
		return (-1);
	if (map_check_first_ch(check) == -1)
		return (-1);
	if (map_check_end_ch(check) == -1)
		return (-1);
	if (map_check_wall_next(check) == -1)
		return (-1);
	if (map_check_wall_prev(check) == -1)
		return (-1);
	if (map_check_space(check) == -1)
		return (-1);
	return (0);
}

static int	map_zero_one(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->map_h)
	{
		x = 0;
		while (x < info->map_w)
		{
			if (info->world_map[y][x] == 0 || info->world_map[y][x] == 1)
			{
				x++;
				continue ;
			}
			else
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

int	map_check(t_map **map_ptr, t_info *info)
{
	t_map	*check;

	check = *map_ptr;
	if (map_check_empty(&check) == -1)
		return (-1);
	if (map_check_identifier(&check, info) == -1)
		return (-1);
	if (map_check_wall(&check) == -1)
		return (-1);
	if (map_to_int(info, &check) == -1)
		return (-1);
	if (map_check_character(info) == -1)
		return (error(NO_CHARACTER));
	if (map_zero_one(info) == -1)
		return (-1);
	return (0);
}
