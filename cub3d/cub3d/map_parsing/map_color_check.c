/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:50:06 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:50:07 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	map_check_f_color(char **texture, t_info *info)
{
	char	*color;
	int		index;

	color = *texture;
	index = 0;
	info->color.f_color1 = malloc_color(color, &index);
	if (info->color.f_color1 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	info->color.f_color2 = malloc_color(color, &index);
	if (info->color.f_color2 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	info->color.f_color3 = malloc_color(color, &index);
	if (info->color.f_color3 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	return (0);
}

int	map_check_c_color(char **texture, t_info *info)
{
	char	*color;
	int		index;

	color = *texture;
	index = 0;
	info->color.c_color1 = malloc_color(color, &index);
	if (info->color.c_color1 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	info->color.c_color2 = malloc_color(color, &index);
	if (info->color.c_color2 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	info->color.c_color3 = malloc_color(color, &index);
	if (info->color.c_color3 == NULL)
		return (-1);
	if (check_comma_space(color, &index) == -1)
		return (-1);
	return (0);
}
