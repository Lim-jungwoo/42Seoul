/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:52:31 by jlim              #+#    #+#             */
/*   Updated: 2020/12/24 15:38:29 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*temp;
	const char	*s_str;
	size_t		s_strlen;
	size_t		i;

	s_strlen = 0;
	s_str = s1;
	i = 0;
	while (*s_str++)
		s_strlen++;
	temp = (char *)malloc(s_strlen + 1);
	if (temp == 0)
		return (temp);
	while (*s1)
		temp[i++] = *s1++;
	temp[i] = 0;
	return (temp);
}
