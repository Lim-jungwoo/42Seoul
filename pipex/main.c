/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:11:05 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 16:10:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_copy_environ(char **environ, char ***env)
{
	int	i;
	int	j;

	i = 0;
	while (environ[i] != NULL)
		i++;
	if (!((*env) = (char **)malloc(sizeof(char *) * (i + 1))))
		print_error(2);
	i = 0;
	while (environ[i] != NULL)
	{
		j = ft_strlen(environ[i]);
		if (!((*env)[i] = (char *)malloc(sizeof(char) * (j + 1))))
			print_error(2);
		j = -1;
		while (environ[i][++j])
			(*env)[i][j] = environ[i][j];
		(*env)[i][j] = '\0';
		i++;
	}
	(*env)[i] = NULL;
}

int		main(int ac, char **av)
{
	extern char	**environ;
	t_cmd		*arg;
	char		**env;

	ft_copy_environ(environ, &env);
	if (ac != 5)
		print_error(1);
	if (!(arg = (t_cmd *)malloc(sizeof(t_cmd))))
		print_error(2);
	arg->av = av;
	arg->env = env;
	ft_pipe(arg);
	return (0);
}
