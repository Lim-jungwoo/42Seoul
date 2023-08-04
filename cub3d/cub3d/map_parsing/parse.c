/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:33:43 by jlim              #+#    #+#             */
/*   Updated: 2022/03/08 13:33:44 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_raycast.h"

int	sub_gnl(char **str, ssize_t ret)
{
	if (ret == 0)
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	ssize_t	ret;
	char	*str;
	char	*tmp;
	char	buf[2];

	buf[1] = '\0';
	ret = read(fd, buf, 1);
	str = ft_strdup("");
	if (str == NULL)
		return (error(GNL_MALLOC_FAIL));
	if (sub_gnl(&str, ret) == 1)
		return (0);
	while (ret > 0 && buf[0] != '\n')
	{
		tmp = str;
		str = ft_strjoin(tmp, buf);
		free(tmp);
		if (str == NULL)
			return (error(GNL_MALLOC_FAIL));
		ret = read(fd, buf, 1);
	}
	*line = str;
	if (ret < 0)
		return (error(READ_FAIL));
	return (1);
}

int	add_line_to_map(char *line, t_map **map_ptr)
{
	t_map	*ptr;

	if (*map_ptr == NULL)
	{
		*map_ptr = malloc(sizeof(t_map));
		if (*map_ptr == NULL)
			return (error(MAP_MALLOC_FAIL));
		(*map_ptr)->line = line;
		(*map_ptr)->next = NULL;
		(*map_ptr)->prev = NULL;
	}
	else
	{
		ptr = *map_ptr;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = malloc(sizeof(t_map));
		if (ptr->next == NULL)
			return (error(MAP_MALLOC_FAIL));
		ptr->next->line = line;
		ptr->next->next = NULL;
		ptr->next->prev = ptr;
	}
	return (0);
}

int	parse_gnl(t_map **map_ptr, const int fd)
{
	int		ret_gnl;
	int		ret_add_line;
	char	*line;

	line = NULL;
	ret_gnl = get_next_line(fd, &line);
	ret_add_line = 0;
	while (ret_gnl > 0 && ret_add_line == 0)
	{
		ret_add_line = add_line_to_map(line, map_ptr);
		line = NULL;
		ret_gnl = get_next_line(fd, &line);
	}
	if (ret_gnl < 0 || ret_add_line < 0)
		return (-1);
	return (0);
}

int	parse_map(t_map **map_ptr, const char *map_file, t_info *info)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (error(OPEN_FAIL));
	if (parse_gnl(map_ptr, fd) == -1)
		return (-1);
	if (close(fd))
		return (error(CLOSE_FAIL));
	if (map_check(map_ptr, info) == -1)
		return (error(INVALID_MAP));
	map_clear(map_ptr);
	return (0);
}
