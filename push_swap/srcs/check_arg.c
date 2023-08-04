/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:27:48 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:32:16 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	arg_count(char **av)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = 1;
	j = 0;
	count = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 4000000000)
		{
			split = ft_split(av[i], ' ');
			while (split[j++])
				count++;
			j = 0;
			free_split(split);
		}
		else
			count++;
		i++;
	}
	return (count);
}

static int	arg_num(char **av, long long **val)
{
	int			count;
	char		**split;
	int			i;
	int			j;

	*val = (long long *)malloc(sizeof(long long) * arg_count(av));
	if (!(*val))
		return (0);
	i = 1;
	count = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) == 4000000000)
		{
			split = ft_split(av[i], ' ');
			j = 0;
			while (split[j])
				val[0][count++] = ft_atoi(split[j++]);
			free_split(split);
		}
		else
			val[0][count++] = ft_atoi(av[i]);
		i++;
	}
	return (1);
}

int	check_arg(char **av, long long **val)
{
	int			i;
	int			j;
	long long	num;

	i = 0;
	j = 0;
	if (!arg_num(av, val))
		return (0);
	while (i < arg_count(av))
	{
		num = val[0][i];
		if (num == 3000000000 || num < -2147483648 || num > 2147483647)
			return (0);
		i++;
	}
	return (1);
}
