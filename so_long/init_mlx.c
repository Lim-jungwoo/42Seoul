/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 12:43:40 by jlim              #+#    #+#             */
/*   Updated: 2021/06/25 11:48:28 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_images(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	mlx->sprit1_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "picture/player.xpm",
			&(mlx->size_square), &(mlx->size_square));
	mlx->sprit2_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "picture/collect.xpm",
			&(mlx->size_square), &(mlx->size_square));
	mlx->sprit3_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "picture/exit.xpm",
			&(mlx->size_square), &(mlx->size_square));
	mlx->sprit4_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "picture/wall.xpm",
			&(mlx->size_square), &(mlx->size_square));
}

static void	init_data_images(t_mlx *mlx)
{
	mlx->img = mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
			&(mlx->size_line), &(mlx->endian));
	mlx->sprit1 = mlx_get_data_addr(mlx->sprit1_ptr, &(mlx->bpp),
			&(mlx->size_square), &(mlx->endian));
	mlx->sprit2 = mlx_get_data_addr(mlx->sprit2_ptr, &(mlx->bpp),
			&(mlx->size_square), &(mlx->endian));
	mlx->sprit3 = mlx_get_data_addr(mlx->sprit3_ptr, &(mlx->bpp),
			&(mlx->size_square), &(mlx->endian));
	mlx->sprit4 = mlx_get_data_addr(mlx->sprit4_ptr, &(mlx->bpp),
			&(mlx->size_square), &(mlx->endian));
}

int			init_mlx(t_mlx *mlx, t_map *map)
{
	mlx->map = map;
	mlx->width = 40 * map_width(map);
	mlx->height = 40 * map_height(map);
	mlx->move_count = 0;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (7);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, mlx->width,
			mlx->height, "so long");
	init_images(mlx);
	if (!mlx->img_ptr || !mlx->sprit1_ptr || !mlx->sprit2_ptr ||
			!mlx->sprit3_ptr || !mlx->sprit4_ptr)
		return (8);
	init_data_images(mlx);
	return (0);
}
