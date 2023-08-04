/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:50:32 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:50:32 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

static void	malloc_error(int **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

static int	**malloc_map(int **map, int hei, int wid)
{
	int	i;

	map = (int **)malloc(sizeof(int *) * hei);
	if (map == NULL)
	{
		free(map);
		map = NULL;
		return (NULL);
	}
	i = -1;
	while (++i < hei)
	{
		map[i] = (int *)malloc(sizeof(int) * wid);
		if (map[i] == NULL)
		{
			malloc_error(map);
			return (NULL);
		}
	}
	return (map);
}

static void	get_int_map(t_info *info, t_map *check, int **map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->map_h)
	{
		j = -1;
		while (++j < info->map_w)
		{
			if (check->line[j] == ' ')
				map[i][j] = 1;
			else if ((int)ft_strlen(check->line) < info->map_w
				&& (int)ft_strlen(check->line) <= j)
				map[i][j] = 1;
			else
				map[i][j] = check->line[j] - '0';
		}
		check = check->next;
	}
}

int	map_to_int(t_info *info, t_map **map_ptr)
{
	int		**map;
	t_map	*check;

	check = *map_ptr;
	info->map_w = map_width(&check);
	info->map_h = map_height(&check);
	map = NULL;
	map = malloc_map(map, info->map_h, info->map_w);
	if (!map)
		return (error(INT_MAP_MALLOC_FAIL));
	get_int_map(info, check, map);
	info->world_map = map;
	return (0);
}
