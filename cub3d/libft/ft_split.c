/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:05:19 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:32:00 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*result;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		return (0);
	i = 0;
	while (i < n)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

static void	ft_free_arr(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;
	size_t	wordlen;
	size_t	i;

	count = ft_count_word(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	i = -1;
	while (++i < count)
	{
		while (*s && *s == c)
			s++;
		wordlen = ft_wordlen(s, c);
		result[i] = ft_strndup(s, wordlen);
		if (!result[i])
		{
			ft_free_arr(result, i - 1);
			return (0);
		}
		s += wordlen;
	}
	result[count] = 0;
	return (result);
}
