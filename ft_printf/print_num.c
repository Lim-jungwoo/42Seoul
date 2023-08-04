/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:43:31 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 17:57:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	num_no_hyphen(char *str, int width, t_info info, int sign)
{
	char	*fill_value;
	int		str_len;
	int		pre_num;
	int		flag;

	flag = 0;
	str_len = ft_strlen(str);
	pre_num = (info.p_num > str_len) ? info.p_num - str_len : 0;
	fill_value = (info.f_zero == YES && (info.p_is == NODOT
				|| info.p_num < 0)) ? "0" : " ";
	if (sign < 0 && info.f_zero == YES && width > 0
			&& (info.p_num < 0 || info.p_is == NODOT))
	{
		write(1, "-", sizeof(char));
		flag = 1;
	}
	if (width > 0)
		while (width--)
			write(1, fill_value, sizeof(char));
	if (sign < 0 && flag == 0)
		write(1, "-", sizeof(char));
	while (pre_num--)
		write(1, "0", sizeof(char));
	write(1, str, sizeof(char) * ft_strlen(str));
}

void	num_is_hyphen(char *str, int width, int pre_num, int sign)
{
	if (sign < 0)
		write(1, "-", sizeof(char));
	while (pre_num--)
		write(1, "0", sizeof(char));
	write(1, str, sizeof(char) * ft_strlen(str));
	if (width > 0)
		while (width--)
			write(1, " ", sizeof(char));
}

int		print_num(char *str, t_info info, int sign)
{
	int	str_len;
	int	width;
	int	pre_num;
	int	print_len;

	width = 0;
	str_len = ft_strlen(str);
	pre_num = (info.p_num > str_len) ? info.p_num - str_len : 0;
	print_len = pre_num + str_len;
	width = (pre_num > 0) ? (info.w_num - info.p_num) : (info.w_num - str_len);
	if (sign < 0)
		width--;
	if (width > 0)
		print_len += width;
	if (info.f_hyphen == YES)
		num_is_hyphen(str, width, pre_num, sign);
	else
		num_no_hyphen(str, width, info, sign);
	return (print_len);
}
