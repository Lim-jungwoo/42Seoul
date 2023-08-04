/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:30:54 by jlim              #+#    #+#             */
/*   Updated: 2022/04/05 15:26:13 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	itoa_strlen(long long int n)
{
	long long	number;
	int			n_strlen;
	long long	check_digit;

	n_strlen = 0;
	number = n;
	check_digit = 1;
	if (n < 0)
	{
		n_strlen++;
		number *= (-1);
	}
	if (n == 0)
		return (1);
	while (1)
	{
		if (number / check_digit > 0)
			n_strlen++;
		if (number < check_digit)
			break ;
		check_digit *= 10;
	}
	return (n_strlen);
}

static int	check_digit_n(long long int n, int n_strlen)
{
	int	i;
	int	digit;

	digit = 1;
	if (n < 0)
		i = n_strlen - 1;
	else
		i = n_strlen;
	while (--i)
		digit *= 10;
	return (digit);
}

static char	*sub_ft_itoa(long long int n, char *str, int check_digit)
{
	int			i;
	long long	number;

	i = 0;
	number = n;
	if (n < 0)
	{
		str[i++] = '-';
		number *= -1;
	}
	while (check_digit)
	{
		str[i++] = (number / check_digit) + '0';
		number -= (number / check_digit) * check_digit;
		check_digit /= 10;
	}
	str[i] = 0;
	return (str);
}

char	*ft_itoa(long long int n)
{
	char		*str;
	int			n_strlen;
	int			check_digit;

	n_strlen = itoa_strlen(n);
	str = (char *)malloc(sizeof(char) * n_strlen + 1);
	if (str == 0)
		return (str);
	check_digit = check_digit_n(n, n_strlen);
	str = sub_ft_itoa(n, str, check_digit);
	return (str);
}
