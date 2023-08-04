/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:40:58 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 16:53:29 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

int	error_2(int error_num)
{
	if (error_num == MAP_EMPTY)
		printf("map has no mandatory part\n");
	else if (error_num == ERROR_FLAG)
		printf("map_file has invalid flag\n");
	else if (error_num == ERROR_COLOR)
		printf("map_file has invalid color\n");
	else if (error_num == INVALID_MAP)
		printf("map_file has invalid map\n");
	else if (error_num == ERROR_ELEMENT)
		printf("map_file has invalid element\n");
	else if (error_num == NO_WALL)
		printf("map is not surrounded by wall\n");
	else if (error_num == INT_MAP_MALLOC_FAIL)
		printf("failed to malloc int **world_map\n");
	return (-1);
}

int	error(int error_num)
{
	if (error_num == NOT_ARGUMENT)
		printf("please use ./cub3d map\n");
	else if (error_num == NOT_CUB)
		printf("map_file is not .cub\n");
	else if (error_num == OPEN_FAIL)
		printf("map_file open fail\n");
	else if (error_num == READ_FAIL)
		printf("map_file read fail\n");
	else if (error_num == GNL_MALLOC_FAIL)
		printf("GNL malloc fail\n");
	else if (error_num == MAP_MALLOC_FAIL)
		printf("map malloc fail\n");
	else if (error_num == CLOSE_FAIL)
		printf("map_file close fail\n");
	else if (error_num == INVALID_TEXTURE)
		printf("texture path is invalid\n");
	else if (error_num == NO_CHARACTER)
		printf("map has no character\n");
	else if (error_num == TEXTURE_MALLOC_FAIL)
		printf("texture malloc fail\n");
	else
		return (error_2(error_num));
	return (-1);
}

int	parse_map_error(t_map **map, t_info *info)
{
	map_clear(map);
	int_map_clear(info);
	texture_clear(info);
	char_texture_clear(info);
	char_f_color_clear(info);
	char_c_color_clear(info);
	return (-1);
}

int	load_texture_error(t_info *info)
{	
	int_map_clear(info);
	texture_clear(info);
	char_texture_clear(info);
	char_f_color_clear(info);
	char_c_color_clear(info);
	return (-1);
}
