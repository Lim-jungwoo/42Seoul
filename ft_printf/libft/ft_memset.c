/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:23:27 by jlim              #+#    #+#             */
/*   Updated: 2020/12/21 16:08:47 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int fill_value, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		*((char *)dest + i) = fill_value;
		i++;
	}
	return (dest);
}
