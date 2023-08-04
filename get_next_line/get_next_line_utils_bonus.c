/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:42:17 by jlim              #+#    #+#             */
/*   Updated: 2021/05/12 11:42:19 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int		ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!*s && c == 0)
		return (-1);
	while (*s)
	{
		if ((int)*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *s1)
{
	char		*tmp;
	size_t		s_strlen;
	size_t		i;

	s_strlen = ft_strlen(s1);
	i = 0;
	if (!(tmp = (char *)malloc(s_strlen + 1)))
		return (tmp);
	while (*s1)
		tmp[i++] = *s1++;
	tmp[i] = 0;
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	char	*str;

	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s == 0)
		return (s);
	str = s;
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	*s = 0;
	return (str);
}
