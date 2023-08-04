/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:41 by jlim              #+#    #+#             */
/*   Updated: 2021/10/09 14:11:42 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	t_arg	*arg;

	arg = philo->arg;
	if (arg->total_philo == 1)
	{
		sem_wait(arg->forks_b);
		print_action(arg, philo->philo_id, "has taken a fork");
		return ;
	}
	sem_wait(arg->forks_b);
	print_action(arg, philo->philo_id, "has taken a fork");
	sem_wait(arg->forks_b);
	print_action(arg, philo->philo_id, "has taken a fork");
	sem_wait(arg->eat_check_b);
	print_action(arg, philo->philo_id, "is eating");
	philo->t_last_eat = check_time();
	sem_post(arg->eat_check_b);
	sleeping(arg->time_eat, arg);
	(philo->count_ate)++;
	sem_post(arg->forks_b);
	sem_post(arg->forks_b);
}

void	*die_checker(void *void_philo)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)void_philo;
	arg = philo->arg;
	while (1)
	{
		sem_wait(arg->eat_check_b);
		if (diff_time(philo->t_last_eat, check_time()) > arg->time_die)
		{
			print_action(arg, philo->philo_id, "died");
			arg->die = 1;
			sem_wait(arg->print_b);
			exit(1);
		}
		sem_post(arg->eat_check_b);
		if (arg->die)
			break ;
		usleep(1000);
		if (philo->count_ate >= arg->nb_must_eat && arg->nb_must_eat != -1)
			break ;
	}
	return (NULL);
}

void	processing(void *void_philo)
{
	t_philo	*philo;
	t_arg	*arg;

	philo = (t_philo *)void_philo;
	arg = philo->arg;
	philo->t_last_eat = check_time();
	pthread_create(&(philo->die_check), NULL, die_checker, void_philo);
	if (philo->philo_id % 2)
		usleep(15000);
	while (!(arg->die))
	{
		philo_eat(philo);
		if (arg->total_philo == 1)
			sleeping(arg->time_die + 100, arg);
		if (philo->count_ate >= arg->nb_must_eat && arg->nb_must_eat != -1)
			break ;
		print_action(arg, philo->philo_id, "is sleeping");
		sleeping(arg->time_sleep, arg);
		print_action(arg, philo->philo_id, "is thinking");
	}
	pthread_join(philo->die_check, NULL);
	if (arg->die)
		exit(1);
	exit(0);
}

void	exit_launcher(t_arg *arg)
{
	int	i;
	int	ret;

	i = 0;
	while (i < arg->total_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < arg->total_philo)
				kill(arg->philo[i].proc_id, 15);
			break ;
		}
		i++;
	}
	sem_close(arg->forks_b);
	sem_close(arg->print_b);
	sem_close(arg->eat_check_b);
	sem_unlink("/philo_forks_b");
	sem_unlink("/philo_print_b");
	sem_unlink("/philo_eatcheck_b");
}

int	launcher(t_arg *arg)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = arg->philo;
	arg->start_time = check_time();
	while (++i < arg->total_philo)
	{
		philo[i].proc_id = fork();
		if (philo[i].proc_id < 0)
			return (1);
		if (philo[i].proc_id == 0)
			processing(&(philo[i]));
		usleep(100);
	}
	exit_launcher(arg);
	return (0);
}
