/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:49:14 by jlim              #+#    #+#             */
/*   Updated: 2021/06/25 14:15:25 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_in_map(char c, t_map *map)
{
	char	*line;
	int		player;

	player = 0;
	while (map)
	{
		line = map->line;
		while (*line)
		{
			if (line && *line == 'P' && *line == c && player > 1)
				return (0);
			if (line && *line == c && *line == 'P')
				player++;
			if (line && *line == c && *line != 'P')
				return (1);
			line++;
		}
		map = map->next;
	}
	if (player == 1)
		return (1);
	return (0);
}

static int	is_charset(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'P' || c == 'E');
}

static int	check_line(char *line)
{
	if (*line && *line != '1')
		return (0);
	while (*line && *(line + 1))
	{
		if (!is_charset(*line))
			return (0);
		line++;
	}
	if (*line != '1')
		return (0);
	return (1);
}

int			check_map(t_map **map_ptr)
{
	t_map	*map;
	size_t	len_line;

	map = *map_ptr;
	len_line = ft_strlen(map->line);
	while (map)
	{
		if (ft_strlen(map->line) != len_line || !check_line(map->line))
			return (6);
		map = map->next;
	}
	if (!is_in_map('E', *map_ptr) || !is_in_map('C', *map_ptr)
			|| !is_in_map('P', *map_ptr))
		return (6);
	if (!check_wall(*map_ptr))
		return (6);
	return (0);
}
