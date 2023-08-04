/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 13:59:14 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 14:09:20 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_info(t_info *info)
{
	info->f_hyphen = 0;
	info->f_zero = 0;
	info->w_num = 0;
	info->p_num = 0;
	info->p_is = 0;
	info->p_ast = 0;
}

int		parse_arg(va_list *ap, const char *format)
{
	const char	*spec;
	int			print_len;
	t_info		spec_info;

	spec = format;
	print_len = 0;
	while (*spec)
	{
		if (*spec == '%')
		{
			spec++;
			init_info(&spec_info);
			if (!(spec = (const char *)check_info(ap, spec, &spec_info)))
				return (-1);
			if (!(spec = check_spec(ap, spec, spec_info, &print_len)))
				return (-1);
		}
		else
		{
			ft_putchar_fd(*spec, 1);
			print_len++;
		}
		spec++;
	}
	return (print_len);
}
