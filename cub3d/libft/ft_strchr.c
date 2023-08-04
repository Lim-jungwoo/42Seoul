/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:36:28 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:35:39 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!*s && c == 0)
		return ((char *)s);
	while (*s)
	{
		if ((int)*s == c)
			return ((char *)s);
		s++;
		if (c == 0 && !*s)
			return ((char *)s);
	}
	return (NULL);
}
