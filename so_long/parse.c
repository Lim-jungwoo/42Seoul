/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:34:02 by jlim              #+#    #+#             */
/*   Updated: 2021/06/25 11:48:40 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_next_line(int fd, char **line)
{
	ssize_t		ret;
	char		*str;
	char		*tmp;
	char		buf[2];

	ret = read(fd, buf, 1);
	buf[1] = '\0';
	if (ret <= 0)
		return ((int)ret);
	if (!(str = ft_strdup("")))
		return (-1);
	while (ret > 0 && buf[0] != '\n')
	{
		tmp = str;
		if (!(str = ft_strjoin(tmp, buf)))
			return (-1);
		free(tmp);
		ret = read(fd, buf, 1);
	}
	*line = str;
	return (1);
}

int	add_line_to_map(char *line, t_map **map_ptr)
{
	t_map	*ptr;

	if (*map_ptr == NULL)
	{
		if (!(*map_ptr = (t_map *)malloc(sizeof(t_map))))
			return (0);
		(*map_ptr)->line = line;
		(*map_ptr)->next = NULL;
	}
	else
	{
		ptr = *map_ptr;
		while (ptr->next)
			ptr = ptr->next;
		if (!(ptr->next = (t_map *)malloc(sizeof(t_map))))
			return (0);
		ptr->next->line = line;
		ptr->next->next = NULL;
	}
	return (1);
}

int	parse(t_map **map_ptr, const char *map_file)
{
	int		fd;
	int		ret_gnl;
	int		ret_add_line;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (2);
	line = NULL;
	ret_gnl = get_next_line(fd, &line);
	ret_add_line = 1;
	while (ret_gnl > 0 && ret_add_line)
	{
		ret_add_line = add_line_to_map(line, map_ptr);
		line = NULL;
		ret_gnl = get_next_line(fd, &line);
	}
	if (ret_gnl < 0)
		return (3);
	if (!ret_add_line)
		return (4);
	if (close(fd))
		return (5);
	return (check_map(map_ptr));
}
