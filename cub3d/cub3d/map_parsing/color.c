/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:47:09 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:47:11 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

static void	get_f_color(t_info *info, char *color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->color.f_hex_color1[j] != '\0')
		color[i++] = info->color.f_hex_color1[j++];
	j = 0;
	while (info->color.f_hex_color2[j] != '\0')
		color[i++] = info->color.f_hex_color2[j++];
	j = 0;
	while (info->color.f_hex_color3[j] != '\0')
		color[i++] = info->color.f_hex_color3[j++];
	color[i] = '\0';
}

int	map_f_color(t_info *info)
{
	char	*color;

	info->color.f_hex_color1 = int_to_char_hex(ft_atoi(info->color.f_color1));
	info->color.f_hex_color2 = int_to_char_hex(ft_atoi(info->color.f_color2));
	info->color.f_hex_color3 = int_to_char_hex(ft_atoi(info->color.f_color3));
	if (!info->color.f_hex_color1 || !info->color.f_hex_color2
		|| !info->color.f_hex_color3)
		return (-1);
	color = (char *)malloc(sizeof(char) * (ft_strlen(info->color.f_hex_color1)
				+ ft_strlen(info->color.f_hex_color2)
				+ ft_strlen(info->color.f_hex_color3) + 1));
	if (color == NULL)
		return (-1);
	get_f_color(info, color);
	info->f_color = char_hex_to_int(color);
	free(color);
	return (0);
}

static void	get_c_color(t_info *info, char *color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->color.c_hex_color1[j] != '\0')
		color[i++] = info->color.c_hex_color1[j++];
	j = 0;
	while (info->color.c_hex_color2[j] != '\0')
		color[i++] = info->color.c_hex_color2[j++];
	j = 0;
	while (info->color.c_hex_color3[j] != '\0')
		color[i++] = info->color.c_hex_color3[j++];
	color[i] = '\0';
}

int	map_c_color(t_info *info)
{
	char	*color;

	info->color.c_hex_color1 = int_to_char_hex(ft_atoi(info->color.c_color1));
	info->color.c_hex_color2 = int_to_char_hex(ft_atoi(info->color.c_color2));
	info->color.c_hex_color3 = int_to_char_hex(ft_atoi(info->color.c_color3));
	if (!info->color.c_hex_color1 || !info->color.c_hex_color2
		|| !info->color.c_hex_color3)
		return (-1);
	color = (char *)malloc(sizeof(char) * (ft_strlen(info->color.c_hex_color1)
				+ ft_strlen(info->color.c_hex_color2)
				+ ft_strlen(info->color.c_hex_color3) + 1));
	if (color == NULL)
		return (-1);
	get_c_color(info, color);
	info->c_color = char_hex_to_int(color);
	free(color);
	return (0);
}
