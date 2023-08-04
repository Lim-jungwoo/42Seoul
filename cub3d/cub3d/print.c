/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:29:45 by jlim              #+#    #+#             */
/*   Updated: 2022/03/29 17:08:51 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	map_print(t_map **map_ptr)
{
	t_map	*line;

	line = *map_ptr;
	while (line)
	{
		printf("%s\n", line->line);
		if (line->next)
			line = line->next;
		else
			break ;
	}
}

void	map_print2(t_info	*info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->map_h)
	{
		j = -1;
		while (++j < info->map_w)
		{
			printf("%d", info->world_map[i][j]);
		}
		printf("\n");
	}
}
