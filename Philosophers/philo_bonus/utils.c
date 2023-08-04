/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:34 by jlim              #+#    #+#             */
/*   Updated: 2021/10/09 14:11:35 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;

	n = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + ((*str++) - '0');
		else
			return (-1);
	}
	return ((int)(n));
}

long long	check_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	diff_time(long long past, long long pres)
{
	return (pres - past);
}

void	sleeping(long long time, t_arg *arg)
{
	long long	i;

	i = check_time();
	while (!(arg->die))
	{
		if (diff_time(i, check_time()) >= time)
			break ;
		usleep(50);
	}
}

void	print_action(t_arg *arg, int philo_id, char *str)
{
	sem_wait(arg->print_b);
	if (!(arg->die))
	{
		printf("%lli ", check_time() - arg->start_time);
		printf("%i ", philo_id + 1);
		printf("%s\n", str);
	}
	sem_post(arg->print_b);
}
