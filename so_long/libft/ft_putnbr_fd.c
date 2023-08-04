/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:58:19 by jlim              #+#    #+#             */
/*   Updated: 2021/02/19 11:54:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	long long	number;
	long long	digit;

	number = n;
	digit = 1;
	if (n < 0)
	{
		number *= -1;
		write(fd, "-", 1);
	}
	while (1)
	{
		if (number < (digit * 10))
			break ;
		digit *= 10;
	}
	while (digit)
	{
		ft_putchar_fd((char)(number / digit + '0'), fd);
		number -= (number / digit) * digit;
		digit /= 10;
	}
	return ;
}
