/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:26:04 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 14:34:25 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_check_file(char *s)
{
	int	fd;

	if (access(s, F_OK) == 0)
	{
		if (access(s, R_OK) == 0)
		{
			fd = open(s, O_RDONLY);
			return (fd);
		}
		else
			print_error2(6, s);
	}
	else
		print_error2(7, s);
	return (0);
}

int		ft_check_file_exist(char *s)
{
	int	fd;

	fd = 0;
	if (access(s, F_OK) == 0)
	{
		if (access(s, W_OK) == 0)
		{
			fd = open(s, O_TRUNC | O_WRONLY);
			return (fd);
		}
		else
			print_error2(6, s);
	}
	else
		fd = open(s, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
	return (fd);
}

void	ft_check_retf_retx(t_cmd *arg, int retf, int retx, int childpid)
{
	if (retf == -1)
	{
		if (childpid == 0)
			print_error2(5, arg->cmd1[0]);
		else
			print_error2(5, arg->cmd2[0]);
	}
	else if (retx == -1)
	{
		if (childpid == 0)
			print_error2(5, arg->cmd1[0]);
		else
			print_error2(5, arg->cmd2[0]);
	}
}

char	*ft_check_command(t_cmd *arg, int childpid)
{
	int		i;
	int		retf;
	int		retx;
	char	**path;
	char	*cmd;

	i = -1;
	retf = 0;
	retx = 0;
	if ((path = ft_get_env("PATH", arg->env)) == NULL)
		print_error(4);
	while (path[++i] != NULL)
	{
		if (childpid == 0)
			cmd = ft_strjoin(path[i], arg->cmd1[0]);
		else
			cmd = ft_strjoin(path[i], arg->cmd2[0]);
		if ((retf = access(cmd, F_OK)) == 0)
			if ((retx = access(cmd, X_OK)) == 0)
				return (cmd);
	}
	ft_check_retf_retx(arg, retf, retx, childpid);
	return (NULL);
}
