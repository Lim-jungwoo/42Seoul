/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:26:07 by jlim              #+#    #+#             */
/*   Updated: 2021/02/18 14:44:15 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t count)
{
	unsigned char		*temp;
	const unsigned char	*s;

	temp = dest;
	s = src;
	if (count == 0)
		return (NULL);
	while (count)
	{
		if (*s == (unsigned char)c && count)
		{
			*temp = *s;
			temp++;
			return (temp);
		}
		*temp++ = *s++;
		count--;
	}
	return (NULL);
}
