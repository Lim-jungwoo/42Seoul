/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:57:43 by hyejung           #+#    #+#             */
/*   Updated: 2022/04/07 16:31:14 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	draw(t_info *info)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			info->img.data[y * WIN_WIDTH + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int	main_loop(t_info *info)
{
	floor_ceiling_cast(info);
	wall_cast(info);
	draw(info);
	key_update(info);
	return (0);
}

static void	is_map_cub(char **argv)
{
	char	*map;
	int		i;

	map = *argv;
	i = ft_strlen(map) - 4;
	if (i < 0)
	{
		error(NOT_CUB);
		exit(0);
	}
	if (ft_strcmp(&map[i], ".cub") != 0)
	{
		error(NOT_CUB);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_info	info;

	if (argc != 2)
		return (error(NOT_ARGUMENT));
	is_map_cub(&argv[1]);
	map = NULL;
	init_info(&info);
	if (parse_map(&map, argv[1], &info) == -1)
		return (parse_map_error(&map, &info));
	init_dir(&info);
	if (load_texture(&info) == -1)
		return (load_texture_error(&info));
	info.win = mlx_new_window(info.mlx, WIN_WIDTH, WIN_HEIGHT, "mlx");
	info.img.img = mlx_new_image(info.mlx, WIN_WIDTH, WIN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp,
			&info.img.size_l, &info.img.endian);
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, X_EVENT_KEY_EXIT, 0, &close_win, &info);
	mlx_loop(info.mlx);
}
