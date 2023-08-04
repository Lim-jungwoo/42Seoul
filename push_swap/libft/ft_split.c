/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 12:28:18 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 09:17:42 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

static size_t	split_end(char const *s, char c, size_t end)
{
	while (s[end] == c)
		end++;
	return (end);
}

static size_t	split_start(char const *s, char c, size_t start)
{
	while (s[start] == c)
		start++;
	return (start);
}

static char	**sub_ft_split(char const *s, char **str, char c, size_t idx)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	start = 0;
	while (s[end])
	{
		start = split_start(s, c, start);
		end = split_end(s, c, end);
		if (!s[end])
			break ;
		while (s[end] != c && end < ft_strlen(s))
			end++;
		str[idx] = (char *)malloc(sizeof(char) * (end - start));
		if (str[idx] == 0)
			return (&str[idx]);
		i = 0;
		while (start < end)
			str[idx][i++] = s[start++];
		idx++;
	}
	str[idx] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**str;
	long long	idx;

	idx = 0;
	str = (char **)malloc(sizeof(char *) * ft_strlen(s) + 1);
	if (str == 0)
		return (str);
	str = sub_ft_split(s, str, c, idx);
	return (str);
}
