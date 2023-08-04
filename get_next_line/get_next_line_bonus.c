/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:41:49 by jlim              #+#    #+#             */
/*   Updated: 2021/05/12 11:41:50 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		put_str(char **rd, char **line, int find_n)
{
	char	*tmp;

	(*rd)[find_n] = '\0';
	if (!(*line = ft_strdup(*rd)) ||
			!(tmp = ft_strdup((*rd) + find_n + 1)))
	{
		free(*rd);
		*rd = 0;
		return (-1);
	}
	free(*rd);
	*rd = tmp;
	return (1);
}

int		put_all(char **rd, char **line, ssize_t offset)
{
	int		find_n;

	if (offset < 0)
		return (-1);
	if (*rd && ((find_n = ft_strchr(*rd, '\n')) >= 0))
		return (put_str(rd, line, find_n));
	if (*rd)
	{
		*line = *rd;
		*rd = 0;
	}
	else if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*rd[OPEN_MAX];
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		offset;
	int			find_n;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || !line)
		return (-1);
	while ((offset = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[offset] = '\0';
		if (!(tmp = save_str(rd[fd], buf)))
			return (-1);
		if (rd[fd])
			free(rd[fd]);
		rd[fd] = tmp;
		if ((find_n = ft_strchr(rd[fd], '\n')) >= 0)
			return (put_str(&rd[fd], line, find_n));
	}
	return (put_all(&rd[fd], line, offset));
}
