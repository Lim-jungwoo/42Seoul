/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:22:25 by jlim              #+#    #+#             */
/*   Updated: 2021/02/19 11:08:28 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		dst_strlen;
	size_t		src_strlen;
	const char	*temp;

	dst_strlen = 0;
	src_strlen = 0;
	temp = src;
	while (*dst++)
		dst_strlen++;
	while (*temp++)
		src_strlen++;
	if (dstsize <= dst_strlen)
	{
		dstsize += src_strlen;
		return (dstsize);
	}
	dstsize = dstsize - dst_strlen - 1;
	if (dstsize >= src_strlen)
		dstsize = src_strlen;
	dst--;
	while (dstsize--)
		*dst++ = *src++;
	*dst = 0;
	return (src_strlen + dst_strlen);
}
