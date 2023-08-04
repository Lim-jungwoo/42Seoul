/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:20 by jlim              #+#    #+#             */
/*   Updated: 2021/10/09 14:11:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_semaphore(t_arg *arg)
{
	sem_unlink("/philo_forks_b");
	sem_unlink("/philo_print_b");
	sem_unlink("/philo_eatcheck_b");
	arg->forks_b = sem_open("/philo_forks_b", O_CREAT, S_IRWXU,
			arg->total_philo);
	arg->print_b = sem_open("/philo_print_b", O_CREAT, S_IRWXU, 1);
	arg->eat_check_b = sem_open("/philo_eatcheck_b", O_CREAT, S_IRWXU, 1);
	if (arg->forks_b <= 0 || arg->print_b <= 0 || arg->eat_check_b <= 0)
		return (1);
	return (0);
}

static int	init_philo(t_arg *arg)
{
	int	total_philo;

	total_philo = arg->total_philo;
	arg->philo = (t_philo *)malloc(sizeof(t_philo) * (arg->total_philo));
	if (!arg->philo)
		return (0);
	while (--total_philo >= 0)
	{
		arg->philo[total_philo].philo_id = total_philo;
		arg->philo[total_philo].count_ate = 0;
		arg->philo[total_philo].t_last_eat = 0;
		arg->philo[total_philo].arg = arg;
	}
	return (1);
}

int	init_all(t_arg *arg, char **argv)
{
	arg->total_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->die = 0;
	if (arg->total_philo < 1 || arg->time_die < 0 || arg->time_eat < 0
		|| arg->time_sleep < 0)
		return (1);
	if (argv[5])
	{
		arg->nb_must_eat = ft_atoi(argv[5]);
		if (arg->nb_must_eat <= 0)
			return (1);
	}
	else
		arg->nb_must_eat = -1;
	if (init_semaphore(arg))
		return (2);
	if (!init_philo(arg))
		return (3);
	return (0);
}
