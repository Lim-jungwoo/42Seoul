/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:15:59 by jlim              #+#    #+#             */
/*   Updated: 2021/06/24 19:45:03 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	w_north(t_map *map)
{
	int	i;

	i = 0;
	while (map && (map->line)[i])
	{
		if ((map->line)[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	w_south(t_map *map)
{
	int	i;

	i = 0;
	while (map && map->next)
		map = map->next;
	while (map && (map->line)[i])
	{
		if ((map->line)[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	w_east(t_map *map)
{
	int	i;

	while (map)
	{
		i = 0;
		while ((map->line)[i] && (map->line)[i + 1])
			i++;
		if ((map->line)[i] && (map->line)[i] != '1')
			return (0);
		map = map->next;
	}
	return (1);
}

static int	w_west(t_map *map)
{
	int	i;

	i = 0;
	while (map)
	{
		if ((map->line)[i] && (map->line)[i] != '1')
			return (0);
		map = map->next;
	}
	return (1);
}

int			check_wall(t_map *map)
{
	return (w_north(map) && w_south(map) && w_east(map) && w_west(map));
}
