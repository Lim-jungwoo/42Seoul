/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:21:14 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:27:59 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_start_str(size_t i1, char const *s1, char const *set)
{
	char const	*start_set;

	start_set = set;
	while (i1 < ft_strlen(s1))
	{
		set = start_set;
		while (*set)
		{
			if (s1[i1] == *set)
				break ;
			set++;
		}
		if (!*set)
			break ;
		i1++;
	}
	return (i1);
}

static size_t	find_final_str(size_t i2, char const *s1, char const *set)
{
	char const	*start_set;

	start_set = set;
	while (i2 > 0)
	{
		set = start_set;
		while (*set)
		{
			if (s1[i2] == *set)
				break ;
			set++;
		}
		if (!*set)
			break ;
		i2--;
	}
	return (i2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s;
	char		*str;
	size_t		i1;
	size_t		i2;

	i1 = 0;
	i2 = ft_strlen(s1);
	if (i2 == 0)
		return ((char *)s1);
	i1 = find_start_str(i1, s1, set);
	i2 = find_final_str(i2 - 1, s1, set);
	if (i1 > i2)
		return (ft_strdup(""));
	s = (char *)malloc(sizeof(char) * (i2 - i1 + 2));
	if (s == 0)
		return (s);
	str = s;
	while (i1 <= i2)
		*s++ = s1[i1++];
	*s = 0;
	return (str);
}
