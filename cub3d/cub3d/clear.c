/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:29:50 by jlim              #+#    #+#             */
/*   Updated: 2022/03/29 16:41:14 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	int_map_clear(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->map_h)
	{
		free(info->world_map[i]);
		info->world_map[i] = NULL;
		i++;
	}
	if (info->world_map)
		free(info->world_map);
	info->world_map = NULL;
}

void	texture_clear(t_info *info)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURE)
	{
		free(info->texture[i]);
		info->texture[i] = NULL;
		i++;
	}
	free(info->texture);
	info->texture = NULL;
}

void	char_texture_clear(t_info *info)
{
	if (info->no_texture)
		free(info->no_texture);
	if (info->so_texture)
		free(info->so_texture);
	if (info->we_texture)
		free(info->we_texture);
	if (info->ea_texture)
		free(info->ea_texture);
	info->no_texture = NULL;
	info->so_texture = NULL;
	info->we_texture = NULL;
	info->ea_texture = NULL;
}

void	char_f_color_clear(t_info *info)
{
	if (info->color.f_color)
		free(info->color.f_color);
	if (info->color.f_color1)
		free(info->color.f_color1);
	if (info->color.f_hex_color1)
		free(info->color.f_hex_color1);
	if (info->color.f_color2)
		free(info->color.f_color2);
	if (info->color.f_hex_color2)
		free(info->color.f_hex_color2);
	if (info->color.f_color3)
		free(info->color.f_color3);
	if (info->color.f_hex_color3)
		free(info->color.f_hex_color3);
	info->color.f_color = NULL;
	info->color.f_color1 = NULL;
	info->color.f_color2 = NULL;
	info->color.f_color3 = NULL;
	info->color.f_hex_color1 = NULL;
	info->color.f_hex_color2 = NULL;
	info->color.f_hex_color3 = NULL;
}

void	char_c_color_clear(t_info *info)
{
	if (info->color.c_color)
		free(info->color.c_color);
	if (info->color.c_color1)
		free(info->color.c_color1);
	if (info->color.c_hex_color1)
		free(info->color.c_hex_color1);
	if (info->color.c_color2)
		free(info->color.c_color2);
	if (info->color.c_hex_color2)
		free(info->color.c_hex_color2);
	if (info->color.c_color3)
		free(info->color.c_color3);
	if (info->color.c_hex_color3)
		free(info->color.c_hex_color3);
	info->color.c_color = NULL;
	info->color.c_color1 = NULL;
	info->color.c_color2 = NULL;
	info->color.c_color3 = NULL;
	info->color.c_hex_color1 = NULL;
	info->color.c_hex_color2 = NULL;
	info->color.c_hex_color3 = NULL;
}
