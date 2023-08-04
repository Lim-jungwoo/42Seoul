/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:07:37 by jlim              #+#    #+#             */
/*   Updated: 2021/02/19 11:24:18 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		src_strlen;
	const char	*temp;

	temp = src;
	src_strlen = 0;
	if (!*src)
	{
		*dst = 0;
		return (src_strlen);
	}
	while (*temp++)
		src_strlen++;
	if (dstsize == 0)
		return (src_strlen);
	while (dstsize && *src)
	{
		*dst++ = *src++;
		dstsize--;
	}
	if (*src || (!*src && !dstsize))
		*--dst = 0;
	if (!*src && dstsize)
		*dst = 0;
	return (src_strlen);
}
