/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_map_check_nsew.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:50:40 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:50:41 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	check_f(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[1]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->f_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->f_flag = 1;
	info->color.f_color = map_check_texture(map_ptr);
	if (info->color.f_color == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	if (map_check_f_color(&info->color.f_color, info) == -1)
		return (error(ERROR_COLOR));
	if (map_f_color(info) == -1)
		return (error(ERROR_COLOR));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}

int	check_c(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[1]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->c_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->c_flag = 1;
	info->color.c_color = map_check_texture(map_ptr);
	if (info->color.c_color == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	if (map_check_c_color(&info->color.c_color, info) == -1)
		return (error(ERROR_COLOR));
	if (map_c_color(info) == -1)
		return (error(ERROR_COLOR));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}
