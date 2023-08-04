/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:09:39 by jlim              #+#    #+#             */
/*   Updated: 2021/10/10 13:23:40 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg	arg;
	int		ret;

	if (argc != 5 && argc != 6)
		return (print_error("Wrong argument"));
	ret = init_all(&arg, argv);
	if (ret == 1)
		return (error_manager(ret));
	if (ret == 2)
	{
		free(arg.forks);
		free(arg.philo);
		return (error_manager(ret));
	}
	if (launcher(&arg))
		return (print_error("Thread error"));
	free(arg.forks);
	free(arg.philo);
	return (0);
}
