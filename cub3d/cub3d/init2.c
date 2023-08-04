/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:34:06 by hyejung           #+#    #+#             */
/*   Updated: 2022/03/29 16:53:51 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_raycast.h"

void	dir_north(t_info *info)
{
	double	cos_rad;
	double	sin_rad;
	double	old_dirx;
	double	old_planex;

	cos_rad = M_PI / 2;
	sin_rad = M_PI / 2;
	old_dirx = info->dirx;
	info->dirx = info->dirx * cos(cos_rad) - info->diry * sin(sin_rad);
	info->diry = old_dirx * sin(sin_rad) + info->diry * cos(cos_rad);
	old_planex = info->planex;
	info->planex = info->planex * cos(cos_rad) - info->planey * sin(sin_rad);
	info->planey = old_planex * sin(sin_rad) + info->planey * cos(cos_rad);
}

void	dir_south(t_info *info)
{
	double	cos_rad;
	double	sin_rad;
	double	old_dirx;
	double	old_planex;

	cos_rad = M_PI * 3 / 2;
	sin_rad = M_PI * 3 / 2;
	old_dirx = info->dirx;
	info->dirx = info->dirx * cos(cos_rad) - info->diry * sin(sin_rad);
	info->diry = old_dirx * sin(sin_rad) + info->diry * cos(cos_rad);
	old_planex = info->planex;
	info->planex = info->planex * cos(cos_rad) - info->planey * sin(sin_rad);
	info->planey = old_planex * sin(sin_rad) + info->planey * cos(cos_rad);
}

void	dir_west(t_info *info)
{
	double	cos_rad;
	double	sin_rad;
	double	old_dirx;
	double	old_planex;

	cos_rad = M_PI;
	sin_rad = M_PI;
	old_dirx = info->dirx;
	info->dirx = info->dirx * cos(cos_rad) - info->diry * sin(sin_rad);
	info->diry = old_dirx * sin(sin_rad) + info->diry * cos(cos_rad);
	old_planex = info->planex;
	info->planex = info->planex * cos(cos_rad) - info->planey * sin(sin_rad);
	info->planey = old_planex * sin(sin_rad) + info->planey * cos(cos_rad);
}

void	init_dir(t_info *info)
{
	info->dirx = 0.0;
	info->diry = 1.0;
	info->planex = 0.66;
	info->planey = 0.0;
	if (info->flag.n_flag)
		dir_north(info);
	if (info->flag.s_flag)
		dir_south(info);
	if (info->flag.w_flag)
		dir_west(info);
}

void	init_flag(t_info *info)
{
	info->flag.no_flag = 0;
	info->flag.so_flag = 0;
	info->flag.we_flag = 0;
	info->flag.ea_flag = 0;
	info->flag.f_flag = 0;
	info->flag.c_flag = 0;
	info->flag.n_flag = 0;
	info->flag.s_flag = 0;
	info->flag.e_flag = 0;
	info->flag.w_flag = 0;
}
