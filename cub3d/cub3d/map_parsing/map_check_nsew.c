/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_nsew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:07:37 by jlim              #+#    #+#             */
/*   Updated: 2022/03/10 11:07:40 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

static int	check_no(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[2]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->no_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->no_flag = 1;
	info->no_texture = map_check_texture(map_ptr);
	if (info->no_texture == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}

static int	check_so(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[2]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->so_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->so_flag = 1;
	info->so_texture = map_check_texture(map_ptr);
	if (info->so_texture == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}

static int	check_we(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[2]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->we_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->we_flag = 1;
	info->we_texture = map_check_texture(map_ptr);
	if (info->we_texture == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}

static int	check_ea(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	if (ft_isspace((*map_ptr)->line[2]) == 0)
		return (error(ERROR_FLAG));
	if (nsew_flag->ea_flag == 1)
		return (error(ERROR_FLAG));
	nsew_flag->ea_flag = 1;
	info->ea_texture = map_check_texture(map_ptr);
	if (info->ea_texture == NULL)
		return (error(TEXTURE_MALLOC_FAIL));
	(*map_ptr) = (*map_ptr)->next;
	return (0);
}

int	map_check_nsew(t_map **map_ptr, t_flag *nsew_flag, t_info *info)
{
	int	ret;

	ret = 0;
	while (ft_strcmp((*map_ptr)->line, "") != 0)
	{
		if (ft_strncmp((*map_ptr)->line, "NO", 2) == 0)
			ret = check_no(map_ptr, nsew_flag, info);
		else if (ft_strncmp((*map_ptr)->line, "SO", 2) == 0)
			ret = check_so(map_ptr, nsew_flag, info);
		else if (ft_strncmp((*map_ptr)->line, "WE", 2) == 0)
			ret = check_we(map_ptr, nsew_flag, info);
		else if (ft_strncmp((*map_ptr)->line, "EA", 2) == 0)
			ret = check_ea(map_ptr, nsew_flag, info);
		else if (ft_strncmp((*map_ptr)->line, "F", 1) == 0)
			ret = check_f(map_ptr, nsew_flag, info);
		else if (ft_strncmp((*map_ptr)->line, "C", 1) == 0)
			ret = check_c(map_ptr, nsew_flag, info);
		else
			return (error(ERROR_FLAG));
		if (ret == -1)
			return (ret);
	}
	return (ret);
}
