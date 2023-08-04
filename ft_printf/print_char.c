/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:10:02 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 17:16:38 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_no_hyphen(char *fill_value, char *str, int width, size_t len)
{
	while (width--)
		write(1, fill_value, sizeof(char));
	write(1, str, sizeof(char) * len);
}

void	char_is_hyphen(char *fill_value, char *str, int width, size_t len)
{
	write(1, str, sizeof(char) * len);
	while (width--)
		write(1, fill_value, sizeof(char));
}

int		print_char(const char *spec, char *str, t_info info, size_t len)
{
	int		width;
	char	*fill_value;
	int		print_len;

	fill_value = " ";
	if (*spec == '%' && info.f_zero == YES && info.f_hyphen == NO)
		fill_value = "0";
	if ((int)len > info.w_num)
		width = 0;
	else
		width = info.w_num - len;
	print_len = width + len;
	if (info.f_hyphen == YES)
		char_is_hyphen(fill_value, str, width, len);
	else
		char_no_hyphen(fill_value, str, width, len);
	return (print_len);
}
