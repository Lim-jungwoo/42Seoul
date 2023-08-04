/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:24:11 by jlim              #+#    #+#             */
/*   Updated: 2021/06/25 12:23:01 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_sprit(t_mlx *mlx, int width, int height)
{
	if (map_index(mlx->map, width / 40, height / 40) == '0')
		((int *)(mlx->img))[height * mlx->width + width] = FONT_COLOR;
	else if (map_index(mlx->map, width / 40, height / 40) == 'P')
		((int *)(mlx->img))[height * mlx->width + width] =
			((int *)(mlx->sprit1))[height % 40 * 40 + width % 40];
	else if (map_index(mlx->map, width / 40, height / 40) == 'C')
		((int *)(mlx->img))[height * mlx->width + width] =
			((int *)(mlx->sprit2))[height % 40 * 40 + width % 40];
	else if (map_index(mlx->map, width / 40, height / 40) == 'E')
		((int *)(mlx->img))[height * mlx->width + width] =
			((int *)(mlx->sprit3))[height % 40 * 40 + width % 40];
	else if (map_index(mlx->map, width / 40, height / 40) == '1')
		((int *)(mlx->img))[height * mlx->width + width] =
			((int *)(mlx->sprit4))[height % 40 * 40 + width % 40];
	if (((int *)(mlx->img))[height * mlx->width + width] == -16777216)
		((int *)(mlx->img))[height * mlx->width + width] = FONT_COLOR;
}

static int	display(t_mlx *mlx)
{
	int	width;
	int	height;

	width = 0;
	while (width < mlx->width)
	{
		height = 0;
		while (height < mlx->height)
		{
			print_sprit(mlx, width, height);
			height++;
		}
		width++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->img_ptr, 0, 0);
	return (0);
}

static int	keypress(int key, t_mlx *mlx)
{
	char	*count;

	if (key == A_KEY)
		move_left(mlx);
	else if (key == D_KEY)
		move_right(mlx);
	else if (key == W_KEY)
		move_up(mlx);
	else if (key == S_KEY)
		move_down(mlx);
	else if (key == ESC_KEY)
		close_win(mlx);
	count = ft_itoa(mlx->move_count);
	write(1, count, ft_strlen(count));
	free(count);
	write(1, "\r", 1);
	return (0);
}

int			play(t_map *map)
{
	t_mlx	mlx;
	int		err_num;

	if ((err_num = init_mlx(&mlx, map)))
		return (err_num);
	mlx_hook(mlx.mlx_win, 2, (1L << 0), keypress, (void *)&mlx);
	mlx_hook(mlx.mlx_win, 17, (1L << 17), close_win, (void *)&mlx);
	mlx_loop_hook(mlx.mlx_ptr, display, (void *)&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
