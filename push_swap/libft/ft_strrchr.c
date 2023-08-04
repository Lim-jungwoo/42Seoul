/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:45:52 by jlim              #+#    #+#             */
/*   Updated: 2021/02/19 10:42:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = NULL;
	if (!*s && c == 0)
		result = (char *)s;
	while (*s)
	{
		if ((int)*s == c)
			result = (char *)s;
		s++;
		if (!*s && c == 0)
			result = (char *)s;
	}
	return (result);
}
