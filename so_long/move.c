/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:25:18 by jlim              #+#    #+#             */
/*   Updated: 2021/06/24 15:48:27 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move(t_mlx *mlx, char *from, char *to)
{
	*from = '0';
	*to = 'P';
	mlx->move_count++;
}

void		move_left(t_mlx *mlx)
{
	t_map	*map;
	int		i;

	map = mlx->map;
	while (map)
	{
		i = -1;
		while ((map->line)[++i])
		{
			if ((map->line)[i] == 'P' && i > 0 && (map->line)[i - 1] == 'E')
			{
				if (!is_fish(mlx->map))
					close_win(mlx);
			}
			else if ((map->line)[i] == 'P' && i > 0 &&
					(map->line)[i - 1] != '1')
				return (move(mlx, &((map->line)[i]), &((map->line)[i - 1])));
		}
		map = map->next;
	}
}

void		move_right(t_mlx *mlx)
{
	t_map	*map;
	int		i;

	map = mlx->map;
	while (map)
	{
		i = -1;
		while ((map->line)[++i])
		{
			if ((map->line)[i] == 'P' && (map->line)[i + 1] &&
					(map->line)[i + 1] == 'E')
			{
				if (!is_fish(mlx->map))
					close_win(mlx);
			}
			else if ((map->line)[i] == 'P' && (map->line)[i + 1] &&
					(map->line)[i + 1] != '1')
				return (move(mlx, &((map->line)[i]), &((map->line)[i + 1])));
		}
		map = map->next;
	}
}

void		move_up(t_mlx *mlx)
{
	t_map	*map;
	int		i;

	map = mlx->map;
	while (map && map->next)
	{
		i = -1;
		while ((map->next->line)[++i])
		{
			if ((map->next->line)[i] == 'P' && (map->line)[i] == 'E')
			{
				if (!is_fish(mlx->map))
					close_win(mlx);
			}
			else if ((map->next->line)[i] == 'P' && (map->line)[i] != '1')
				return (move(mlx, &((map->next->line)[i]), &((map->line)[i])));
		}
		map = map->next;
	}
}

void		move_down(t_mlx *mlx)
{
	t_map	*map;
	int		i;

	map = mlx->map;
	while (map && map->next)
	{
		i = -1;
		while ((map->line)[++i])
		{
			if ((map->line)[i] == 'P' && (map->next->line)[i] == 'E')
			{
				if (!is_fish(mlx->map))
					close_win(mlx);
			}
			else if ((map->line)[i] == 'P' && (map->next->line)[i] != '1')
				return (move(mlx, &((map->line)[i]), &((map->next->line)[i])));
		}
		map = map->next;
	}
}
