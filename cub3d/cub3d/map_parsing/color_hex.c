/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:47:27 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:47:28 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

char	*int_to_char_hex(int color)
{
	int		c1;
	int		c2;
	char	*ret;

	c1 = color / 16;
	if (c1 > 15)
		return (NULL);
	c2 = color % 16;
	ret = (char *)malloc(sizeof(char) * 3);
	if (ret == NULL)
		return (NULL);
	ret[0] = "0123456789abcdef"[c1];
	ret[1] = "0123456789abcdef"[c2];
	ret[2] = '\0';
	return (ret);
}

static void	sub_char_hex_to_int(char *color, int *ret, int *hex_i, int *color_i)
{
	int	i;

	while (*color_i < 6)
	{
		*hex_i = 0;
		i = 1;
		while (*hex_i < 16)
		{
			if ("0123456789abcdef"[*hex_i] == color[*color_i])
			{
				while (6 - *color_i > i)
				{
					*hex_i *= 16;
					i++;
				}
				*ret += *hex_i;
			}
			(*hex_i)++;
		}
		(*color_i)++;
	}
}

int	char_hex_to_int(char *color)
{
	int	hex_i;
	int	color_i;
	int	ret;

	color_i = 0;
	ret = 0;
	sub_char_hex_to_int(color, &ret, &hex_i, &color_i);
	return (ret);
}
