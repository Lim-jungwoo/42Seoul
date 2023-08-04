/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:11:23 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 16:15:01 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(t_cmd *arg, int childpid)
{
	char	*cmd;

	close(arg->fd[0]);
	close(arg->fd[1]);
	if (childpid == 0)
	{
		arg->cmd1 = ft_strsplit(arg->av[2], ' ');
		cmd = ft_check_command(arg, childpid);
		if (execve(cmd, arg->cmd1, arg->env) == -1)
			print_error2(8, cmd);
	}
	else
	{
		arg->cmd2 = ft_strsplit(arg->av[3], ' ');
		cmd = ft_check_command(arg, childpid);
		if (execve(cmd, arg->cmd2, arg->env) == -1)
			print_error2(8, cmd);
	}
}

void	ft_pipe(t_cmd *arg)
{
	int	childpid;
	int	fd;
	int	fd2;

	pipe(arg->fd);
	if ((childpid = fork()) == -1)
		print_error(3);
	if (childpid == 0)
	{
		fd = ft_check_file(arg->av[1]);
		dup2(fd, 0);
		dup2(arg->fd[1], 1);
		close(fd);
		ft_execute(arg, childpid);
	}
	if (childpid > 0)
	{
		fd2 = ft_check_file_exist(arg->av[4]);
		dup2(fd2, 1);
		dup2(arg->fd[0], 0);
		close(fd2);
		ft_execute(arg, childpid);
	}
}
