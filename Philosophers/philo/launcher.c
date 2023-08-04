/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:39:57 by jlim              #+#    #+#             */
/*   Updated: 2021/10/10 13:23:21 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_arg	*arg;

	arg = philo->arg;
	if (arg->total_philo == 1)
	{
		pthread_mutex_lock(&(arg->forks[philo->left_fork_philo]));
		print_action(arg, philo->philo_id, "has taken a fork");
		pthread_mutex_unlock(&(arg->forks[philo->left_fork_philo]));
		return ;
	}
	pthread_mutex_lock(&(arg->forks[philo->left_fork_philo]));
	print_action(arg, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(arg->forks[philo->right_fork_philo]));
	print_action(arg, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(arg->eat_check));
	print_action(arg, philo->philo_id, "is eating");
	philo->t_last_eat = check_time();
	pthread_mutex_unlock(&arg->eat_check);
	sleeping(arg->time_eat, arg);
	(philo->count_ate)++;
	pthread_mutex_unlock(&(arg->forks[philo->left_fork_philo]));
	pthread_mutex_unlock(&(arg->forks[philo->right_fork_philo]));
}

void	*p_thread(void *void_philo)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)void_philo;
	arg = philo->arg;
	if (philo->philo_id % 2)
		usleep(15000);
	while (!(arg->die))
	{
		philo_eat(philo);
		if (arg->total_philo == 1)
			sleeping(arg->time_die + 100, arg);
		if (arg->all_eat)
			break ;
		if (arg->total_philo != 1)
		{
			print_action(arg, philo->philo_id, "is sleeping");
			sleeping(arg->time_sleep, arg);
			print_action(arg, philo->philo_id, "is thinking");
		}
	}
	return (NULL);
}

void	exit_launcher(t_arg *arg, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < arg->total_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < arg->total_philo)
		pthread_mutex_destroy(&(arg->forks[i]));
	pthread_mutex_destroy(&(arg->print));
	pthread_mutex_destroy(&(arg->eat_check));
}

void	die_checker(t_arg *arg, t_philo *philo)
{
	int	i;

	while (!(arg->all_eat))
	{
		i = -1;
		while (++i < arg->total_philo && !(arg->die))
		{
			pthread_mutex_lock(&(arg->eat_check));
			if (diff_time(philo[i].t_last_eat, check_time()) > arg->time_die)
			{
				print_action(arg, i, "died");
				arg->die = 1;
			}
			pthread_mutex_unlock(&(arg->eat_check));
			usleep(100);
		}
		if (arg->die)
			break ;
		i = 0;
		while (arg->nb_must_eat != -1 && i < arg->total_philo
			&& philo[i].count_ate >= arg->nb_must_eat - 1)
			i++;
		if (i == arg->total_philo)
			arg->all_eat = 1;
	}
}

int	launcher(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = arg->philo;
	arg->start_time = check_time();
	while (i < arg->total_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, p_thread, &(philo[i])))
		{
			free(arg->forks);
			free(arg->philo);
			return (1);
		}
		philo[i].t_last_eat = check_time();
		i++;
	}
	die_checker(arg, arg->philo);
	exit_launcher(arg, philo);
	return (0);
}
