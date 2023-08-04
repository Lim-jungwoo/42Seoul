/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:43:24 by jlim              #+#    #+#             */
/*   Updated: 2022/03/08 16:43:25 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	map_check_first_ch(t_map **map_ptr)
{
	t_map	*check;
	int		index;
	int		end_flag;

	check = *map_ptr;
	end_flag = 0;
	while (1)
	{
		index = 0;
		while (ft_isspace(check->line[index]) == 1)
			index++;
		if (check->line[index] != '1')
			return (error(ERROR_ELEMENT));
		if (end_flag == 1)
			break ;
		if (check->next)
			check = check->next;
		else
			end_flag = 1;
	}
	return (0);
}

int	map_check_end_ch(t_map **map_ptr)
{
	t_map	*check;
	int		index;
	int		end_flag;

	check = *map_ptr;
	end_flag = 0;
	while (1)
	{
		index = (int)ft_strlen(check->line) - 1;
		if (check->line[index] != '1')
			return (error(ERROR_ELEMENT));
		if (end_flag == 1)
			break ;
		if (check->next)
			check = check->next;
		else
			end_flag = 1;
	}
	return (0);
}

int	map_check_first_line(t_map **map_ptr)
{
	t_map	*check_first;
	int		index;

	check_first = *map_ptr;
	index = 0;
	while (check_first->line[index])
	{
		if (check_first->line[index] != '1' && check_first->line[index] != ' ')
			return (error(NO_WALL));
		index++;
	}
	return (0);
}

int	map_check_end_line(t_map **map_ptr)
{
	t_map	*check_end;
	int		index;

	check_end = *map_ptr;
	index = 0;
	while (check_end->next)
		check_end = check_end->next;
	while (check_end->line[index])
	{
		if (check_end->line[index] != '1' && check_end->line[index] != ' ')
			return (error(NO_WALL));
		index++;
	}
	return (0);
}
