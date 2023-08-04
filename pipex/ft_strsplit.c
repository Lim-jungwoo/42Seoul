/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:56:29 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 16:06:11 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_word_count(char *s, char c)
{
	int	i;
	int	wdcnt;

	i = 0;
	wdcnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			wdcnt++;
			i++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == '\0')
				return (wdcnt);
		}
		i++;
	}
	return (wdcnt);
}

int		ft_word_len(char *s, char c, int *i)
{
	int	j;

	j = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		(*i)++;
		j++;
	}
	return (j);
}

int		*ft_arr_word_len(char *s, char c, int wdcnt)
{
	int	i;
	int	j;
	int	word_len;
	int	*arr_word_len;

	i = 0;
	j = 0;
	word_len = 0;
	if (!(arr_word_len = (int *)malloc(sizeof(int) * (wdcnt + 1))))
		return (NULL);
	while (s[j] != '\0' && i < wdcnt)
	{
		while (s[j] == c)
			j++;
		if (s[j] != c)
			word_len = ft_word_len(s, c, &j);
		arr_word_len[i] = word_len + 1;
		word_len = 0;
		j++;
		i++;
	}
	arr_word_len[i] = 0;
	return (arr_word_len);
}

char	**ft_malloc_word_len_count(char *s, char c)
{
	int		wdcnt;
	int		*arr_word_len;
	char	**malloc_word;

	wdcnt = ft_word_count(s, c);
	if (!(arr_word_len = ft_arr_word_len(s, c, wdcnt)))
		return (NULL);
	if (!(malloc_word = (char **)malloc(sizeof(char *) * (wdcnt + 1))))
		return (NULL);
	while (wdcnt > -1)
	{
		if (!(malloc_word[wdcnt] = (char *)malloc(sizeof(char) *
						(arr_word_len[wdcnt] + 1))))
			return (NULL);
		wdcnt--;
	}
	free(arr_word_len);
	return (malloc_word);
}

char	**ft_strsplit(char *s, char c)
{
	int		i;
	int		j;
	int		s_i;
	char	**split;

	i = 0;
	s_i = 0;
	if (!(split = ft_malloc_word_len_count(s, c)))
		return (NULL);
	while (s[s_i] != '\0')
	{
		j = 0;
		while (s[s_i] == c)
			s_i++;
		if (s[s_i] != '\0')
		{
			while (s[s_i] != c && s[s_i] != '\0')
				split[i][j++] = s[s_i++];
			split[i][j] = '\0';
			i++;
		}
	}
	split[i] = NULL;
	return (split);
}
