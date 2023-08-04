/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:52:39 by jlim              #+#    #+#             */
/*   Updated: 2021/06/11 15:44:33 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_zero(t_info info, long long int num, int *print_len, char *str)
{
	if (num == 0 && ((info.p_is == DOTNUM && info.p_num == 0)
				|| info.p_is == ONLYDOT))
	{
		(*print_len) += info.w_num;
		while (info.w_num--)
			write(1, " ", sizeof(char));
		free(str);
		str = 0;
		return (0);
	}
	return (1);
}

int		apply_int(va_list *ap, t_info info, int *print_len)
{
	char			*int_str;
	long long int	num;
	int				sign;

	sign = 1;
	num = va_arg(*ap, int);
	if (num < 0)
	{
		sign = -1;
		(*print_len)++;
	}
	if (!(int_str = ft_itoa(num * sign)))
		return (0);
	if (info.p_num < 0 && info.p_ast == NO)
		return (0);
	if (!(check_zero(info, num, print_len, int_str)))
		return (1);
	(*print_len) += print_num(int_str, info, sign);
	free(int_str);
	int_str = 0;
	return (1);
}

int		apply_unint(va_list *ap, t_info info, int *print_len)
{
	char			*int_str;
	unsigned int	un_num;
	int				sign;

	sign = 1;
	un_num = va_arg(*ap, unsigned int);
	if (!(int_str = ft_itoa(un_num)))
		return (0);
	if (info.p_num < 0 && info.p_ast == NO)
		return (0);
	if (!(check_zero(info, un_num, print_len, int_str)))
		return (1);
	(*print_len) += print_num(int_str, info, sign);
	free(int_str);
	int_str = 0;
	return (1);
}

int		apply_hex(va_list *ap, const char *spec, t_info info, int *print_len)
{
	char			*hex_str;
	unsigned int	hex_num;
	int				sign;

	sign = 1;
	hex_num = va_arg(*ap, unsigned int);
	if (!(hex_str = change_hex(hex_num, spec)))
		return (0);
	if (info.p_num < 0 && info.p_ast == NO)
		return (0);
	if (!(check_zero(info, hex_num, print_len, hex_str)))
		return (1);
	(*print_len) += print_num(hex_str, info, sign);
	free(hex_str);
	hex_str = 0;
	return (1);
}
