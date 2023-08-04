/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:28:43 by jlim              #+#    #+#             */
/*   Updated: 2021/06/24 15:49:41 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_win(t_mlx *mlx)
{
	char	*count;

	count = ft_itoa(mlx->move_count);
	write(1, count, ft_strlen(count));
	free(count);
	write(1, "\n", 1);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->sprit1_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->sprit2_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->sprit3_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->sprit4_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	map_clear(&mlx->map);
	exit(0);
	return (0);
}

int	is_fish(t_map *map)
{
	int	i;

	while (map)
	{
		i = 0;
		while ((map->line)[i])
		{
			if ((map->line)[i] == 'C')
				return (1);
			i++;
		}
		map = map->next;
	}
	return (0);
}
