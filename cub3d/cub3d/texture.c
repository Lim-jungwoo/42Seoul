/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:00:33 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 17:10:32 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

static int	load_image(t_info *info, int *texture, char **path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->mlx, *path,
			&img->img_width, &img->img_height);
	if (img->img == NULL)
		return (error(INVALID_TEXTURE));
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
	return (0);
}

int	load_texture(t_info *info)
{
	t_img	img;

	img.img = NULL;
	img.data = NULL;
	if (load_image(info, info->texture[0], &info->no_texture, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[1], &info->so_texture, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[2], &info->we_texture, &img) == -1)
		return (-1);
	if (load_image(info, info->texture[3], &info->ea_texture, &img) == -1)
		return (-1);
	return (0);
}
