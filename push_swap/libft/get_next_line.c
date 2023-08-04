/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:55:43 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 17:55:50 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#define BUFFER_SIZE 42

char	*save_str(char *rd, char *buf)
{
	char	*tmp;

	if (!rd)
		tmp = ft_strdup(buf);
	else
		tmp = ft_strjoin(rd, buf);
	if (!tmp)
	{
		if (rd)
		{
			free(rd);
			rd = 0;
		}
		return (NULL);
	}
	return (tmp);
}

int	put_str(char **rd, char **line, int find_n)
{
	char	*tmp;

	(*rd)[find_n] = '\0';
	*line = ft_strdup(*rd);
	tmp = ft_strdup((*rd) + find_n + 1);
	if (!(*line) || !(tmp))
	{
		free(*rd);
		*rd = 0;
		return (-1);
	}
	free(*rd);
	*rd = tmp;
	return (1);
}

int	put_all(char **rd, char **line, ssize_t offset)
{
	int		find_n;

	if (offset < 0)
		return (-1);
	if (*rd)
	{
		find_n = ft_strchr(*rd, '\n');
		if (find_n >= 0)
			return (put_str(rd, line, find_n));
		*line = *rd;
		*rd = 0;
	}
	else
	{
		*line = ft_strdup("");
		if (!(*line))
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*rd[OPEN_MAX];
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		offset;
	int			find_n;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || !line)
		return (-1);
	offset = read(fd, buf, BUFFER_SIZE);
	while (offset > 0)
	{
		buf[offset] = '\0';
		tmp = save_str(rd[fd], buf);
		if (rd[fd])
			free(rd[fd]);
		rd[fd] = tmp;
		find_n = ft_strchr(rd[fd], '\n');
		if (find_n >= 0)
			return (put_str(&rd[fd], line, find_n));
		offset = read(fd, buf, BUFFER_SIZE);
	}
	return (put_all(&rd[fd], line, offset));
}
