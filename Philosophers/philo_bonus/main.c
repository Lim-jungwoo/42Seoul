/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:13 by jlim              #+#    #+#             */
/*   Updated: 2021/10/09 14:11:15 by jlim             ###   ########.fr       */
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
	if (ret)
		return (error_manager(ret));
	if (launcher(&arg))
	{
		free(arg.philo);
		return (print_error("Thread error"));
	}
	free(arg.philo);
	return (0);
}
