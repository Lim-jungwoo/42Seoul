/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:36:28 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 17:57:23 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(char *s, int c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = s;
	if (!*s && c == 0)
		return (-1);
	while (tmp[i])
	{
		if ((int)tmp[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
