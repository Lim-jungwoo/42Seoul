/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:57:41 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:33:44 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*h_temp;
	const char	*n_temp;
	size_t		count;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		count = len--;
		if (*haystack == *needle)
		{
			h_temp = haystack;
			n_temp = needle;
			while (*needle && count--)
			{
				if (*h_temp++ != *needle++)
					break ;
				if (*needle == 0)
					return ((char *)haystack);
			}
			needle = n_temp;
		}
		haystack++;
	}
	return (0);
}
