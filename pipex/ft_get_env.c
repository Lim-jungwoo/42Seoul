/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:39:08 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 13:48:49 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_path(char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
}

char	**ft_get_env(char *s, char **env)
{
	int		i;
	int		j;
	char	**path;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(s, env[i], ft_strlen(s)) == 0)
		{
			j = ft_strichr(env[i], '=');
			path = ft_strsplit(env[i] + j + 1, ':');
			make_path(path);
			return (path);
		}
		i++;
	}
	return (NULL);
}
