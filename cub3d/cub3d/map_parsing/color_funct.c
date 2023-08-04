/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:47:20 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:47:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

static void	check_color(char *color, int *index)
{
	while (1)
	{
		if (ft_isdigit((int)color[*index]))
			(*index)++;
		else
			break ;
	}
}

char	*malloc_color(char *color, int *index)
{
	int		color_start;
	char	*ret;
	int		i;

	color_start = *index;
	i = 0;
	check_color(color, index);
	if (*index - color_start > 3 || *index - color_start == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (*index - color_start + 1));
	if (ret == NULL)
		return (NULL);
	while (color_start < *index)
	{
		ret[i++] = color[color_start];
		color_start++;
	}
	ret[i] = '\0';
	return (ret);
}

int	check_comma_space(char *color, int *index)
{
	if (color[*index] == 0)
		return (0);
	while (ft_isdigit((int)color[*index]) == 0)
	{
		if (!(color[*index] == ',') && !(ft_isspace((int)color[*index])))
			return (-1);
		(*index)++;
	}
	return (0);
}
