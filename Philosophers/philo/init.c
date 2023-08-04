/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:12:32 by jlim              #+#    #+#             */
/*   Updated: 2021/10/09 13:12:33 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_arg *arg)
{
	int	total_philo;

	total_philo = arg->total_philo;
	while (--total_philo >= 0)
	{
		if (pthread_mutex_init(&(arg->forks[total_philo]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(arg->print), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->eat_check), NULL))
		return (1);
	return (0);
}

static int	init_philo(t_arg *arg)
{
	int	total_philo;

	total_philo = arg->total_philo;
	while (--total_philo >= 0)
	{
		arg->philo[total_philo].philo_id = total_philo;
		arg->philo[total_philo].count_ate = 0;
		arg->philo[total_philo].left_fork_philo = total_philo;
		arg->philo[total_philo].right_fork_philo
			= (total_philo + 1) % arg->total_philo;
		arg->philo[total_philo].t_last_eat = 0;
		arg->philo[total_philo].arg = arg;
	}
	return (0);
}

static int	malloc_forks_philo(t_arg *arg)
{
	arg->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (arg->total_philo));
	if (!arg->forks)
		return (0);
	arg->philo = (t_philo *)malloc(sizeof(t_philo) * (arg->total_philo));
	if (!arg->philo)
		return (0);
	return (1);
}

int	init_all(t_arg *arg, char **argv)
{
	arg->total_philo = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->all_eat = 0;
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
	if (!malloc_forks_philo(arg))
		return (1);
	if (init_mutex(arg))
		return (2);
	init_philo(arg);
	return (0);
}
