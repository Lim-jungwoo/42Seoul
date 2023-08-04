/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:37:17 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 16:54:58 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

int	malloc_texture(t_info *info)
{
	int	i;

	info->texture = (int **)malloc(sizeof(int *) * NUM_TEXTURE);
	if (info->texture == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	i = 0;
	while (i < NUM_TEXTURE)
	{
		info->texture[i] = (int *)malloc(sizeof(int)
				* (TEXTURE_HEIGHT * TEXTURE_WIDTH));
		if (info->texture[i] == NULL)
			return (error(TEXTURE_MALLOC_FAIL));
		i++;
	}
	return (0);
}

int	malloc_init_texture(t_info *info)
{
	int	i;
	int	j;

	if (malloc_texture(info) == -1)
		return (-1);
	i = 0;
	while (i < NUM_TEXTURE)
	{
		j = 0;
		while (j < TEXTURE_HEIGHT * TEXTURE_WIDTH)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}
