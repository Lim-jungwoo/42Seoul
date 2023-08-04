/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:32:45 by jlim              #+#    #+#             */
/*   Updated: 2022/03/11 10:32:45 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	map_width(t_map **map_ptr)
{
	t_map	*check;
	int		max;

	check = *map_ptr;
	max = 0;
	while (1)
	{
		if (max < (int)ft_strlen(check->line))
			max = (int)ft_strlen(check->line);
		if (check->next)
			check = check->next;
		else
			break ;
	}
	return (max);
}

int	map_height(t_map **map_ptr)
{
	t_map	*check;
	int		height;

	check = *map_ptr;
	height = 0;
	while (1)
	{
		height++;
		if (check->next)
			check = check->next;
		else
			break ;
	}
	return (height);
}
