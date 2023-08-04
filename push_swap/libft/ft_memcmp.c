/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:42:38 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 16:05:50 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t count)
{
	const char	*str1;
	const char	*str2;

	str1 = s1;
	str2 = s2;
	while (count)
	{
		if (*str1 == 0 && (*str1 != *str2))
			return (*str1 - *str2);
		if (*str1 != *str2)
		{
			if ((*str1 - *str2) < 0 && (unsigned char)(*str1 - *str2) >= 128
					&& (unsigned char)*str1 <= 127)
				return (*str1 - *str2);
			if ((unsigned char)(*str1 - *str2) >= 128)
				return ((unsigned char)(*str1 - *str2));
			else
				return (*str1 - *str2);
		}
		str1++;
		str2++;
		count--;
	}
	return (0);
}
