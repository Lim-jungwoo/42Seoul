/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:40:48 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 16:52:58 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	map_clear(t_map **map_ptr)
{
	t_map	*line;
	t_map	*next;

	line = *map_ptr;
	while (line)
	{
		next = line->next;
		free(line->line);
		line->line = NULL;
		free(line);
		line = NULL;
		line = next;
	}
	*map_ptr = NULL;
}
