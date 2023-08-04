/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:51:45 by jlim              #+#    #+#             */
/*   Updated: 2020/12/24 11:25:44 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char		*temp;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (dest);
	if (dest <= src)
	{
		temp = dest;
		s = src;
		while (count--)
			*temp++ = *s++;
	}
	else
	{
		temp = dest;
		temp += count;
		s = src;
		s += count;
		while (count--)
			*--temp = *--s;
	}
	return (dest);
}
