/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:11:05 by jlim              #+#    #+#             */
/*   Updated: 2021/10/10 14:32:14 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

struct	s_arg;

typedef struct s_philo
{
	int				philo_id;
	int				count_ate;
	int				left_fork_philo;
	int				right_fork_philo;
	long long		t_last_eat;
	struct s_arg	*arg;
	pthread_t		thread_id;
	pthread_t		die_check;
	pid_t			proc_id;
}	t_philo;

typedef struct s_arg
{
	int				total_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	int				die;
	int				all_eat;
	long long		start_time;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	sem_t			*eat_check_b;
	sem_t			*forks_b;
	sem_t			*print_b;
	t_philo			*philo;
}	t_arg;

int			print_error(char *str);
int			error_manager(int error);

int			init_all(t_arg *arg, char **argv);

int			ft_atoi(const char *str);
void		print_action(t_arg *arg, int philo_id, char *str);
long long	check_time(void);
long long	diff_time(long long past, long long pres);
void		sleeping(long long time, t_arg *arg);

int			launcher(t_arg *arg);

#endif
