/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_wall2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:49:04 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:49:05 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

static int	map_check_space_error(int index, t_map *check)
{
	if (index > 0)
	{
		if (check->line[index - 1] != ' ' && check->line[index - 1] != '1')
			return (error(ERROR_ELEMENT));
	}
	if (index < (int)ft_strlen(check->line) - 1)
	{
		if (check->line[index + 1] != ' ' && check->line[index + 1] != '1')
			return (error(ERROR_ELEMENT));
	}
	if (check->prev)
	{
		if ((check->prev->line[index] != ' ' && check->prev->line[index] != '1')
			&& ft_strcmp(check->prev->line, "") != 0)
			return (error(ERROR_ELEMENT));
	}
	if (check->next)
	{
		if (check->next->line[index] != ' ' && check->next->line[index] != '1')
			return (error(ERROR_ELEMENT));
	}
	return (0);
}

int	map_check_space(t_map **map_ptr)
{
	t_map	*check;
	int		index;
	int		end_flag;

	check = *map_ptr;
	end_flag = 0;
	while (1)
	{
		index = 0;
		while (check->line[index])
		{
			if (check->line[index] == ' ')
				if (map_check_space_error(index, check) == -1)
					return (-1);
			index++;
		}
		if (end_flag == 1)
			break ;
		if (check->next)
			check = check->next;
		else
			end_flag = 1;
	}
	return (0);
}

int	map_check_wall_next(t_map **map_ptr)
{
	t_map	*check;
	int		end;
	int		end_next;

	check = *map_ptr;
	while (check->next)
	{
		end = (int)ft_strlen(check->line);
		end_next = (int)ft_strlen(check->next->line) - 1;
		if (end_next >= end)
		{
			while (check->next->line[end])
			{
				if (check->next->line[end] != '1')
					return (error(ERROR_ELEMENT));
				end++;
			}
		}
		check = check->next;
	}
	return (0);
}

int	map_check_wall_prev(t_map **map_ptr)
{
	t_map	*check;
	t_map	*first;
	int		end;
	int		end_prev;

	check = *map_ptr;
	first = *map_ptr;
	while (check->next)
		check = check->next;
	while (check != first)
	{
		end = (int)ft_strlen(check->line);
		end_prev = (int)ft_strlen(check->prev->line) - 1;
		if (end_prev >= end)
		{
			while (check->prev->line[end])
			{
				if (check->prev->line[end] != '1')
					return (error(ERROR_ELEMENT));
				end++;
			}
		}
		check = check->prev;
	}
	return (0);
}
