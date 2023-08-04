/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_identifier.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:48:49 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:48:50 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

char	*map_check_texture(t_map **map_ptr)
{
	char	*texture;
	int		i;

	i = 0;
	while (ft_isspace((*map_ptr)->line[i]) == 0)
		i++;
	if (ft_isspace((*map_ptr)->line[i]) == 0)
		return (NULL);
	while (ft_isspace((*map_ptr)->line[i]))
		i++;
	texture = ft_strdup((&(*map_ptr)->line[i]));
	if (texture == NULL)
		return (NULL);
	return (texture);
}

int	map_check_identifier(t_map **map_ptr, t_info *info)
{
	while (!info->flag.no_flag || !info->flag.so_flag || !info->flag.we_flag
		|| !info->flag.ea_flag || !info->flag.f_flag || !info->flag.c_flag)
	{
		if (map_check_nsew(map_ptr, &info->flag, info) == -1)
			return (-1);
		if (map_check_empty(map_ptr) == -1)
			return (-1);
	}
	return (0);
}
