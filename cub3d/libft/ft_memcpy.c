/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:10:14 by jlim              #+#    #+#             */
/*   Updated: 2020/12/24 11:21:37 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	char		*temp;
	const char	*s;

	temp = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (dest);
	while (count--)
		*temp++ = *s++;
	return (dest);
}
