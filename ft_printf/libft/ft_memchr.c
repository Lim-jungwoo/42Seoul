/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:09:54 by jlim              #+#    #+#             */
/*   Updated: 2020/12/22 15:39:56 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t count)
{
	const char	*temp;

	temp = s;
	while (count--)
	{
		if (*temp == (char)c)
			return (void *)temp;
		temp++;
	}
	return (NULL);
}
