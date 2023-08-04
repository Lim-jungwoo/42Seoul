/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:06:51 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:18:46 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	atoi_util(const char **str, int *min)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '-')
	{
		(*str)++;
		(*min)++;
	}
	else if (**str == '+')
		(*str)++;
	return ;
}

long long	ft_atoi(const char *str)
{
	long long	number;
	int			min;

	number = 0;
	min = 0;
	atoi_util(&str, &min);
	if (*str < '0' || *str > '9')
		return (3000000000);
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += (*str - '0');
		str++;
	}
	if (*str && *str == ' ')
		return (4000000000);
	if (*str && (*str < '0' || *str > '9'))
		return (3000000000);
	if (min == 1)
		number *= -1;
	return (number);
}
