/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:45:36 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 15:49:31 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*check_spec(va_list *ap, const char *spec,
		t_info info, int *print_len)
{
	int	error_check;

	error_check = 0;
	if (*spec == '%')
		error_check = apply_percent(spec, info, print_len);
	else if (*spec == 'c')
		error_check = apply_char(ap, spec, info, print_len);
	else if (*spec == 's')
		error_check = apply_str(ap, spec, info, print_len);
	else if (*spec == 'p')
		error_check = apply_pointer(ap, spec, info, print_len);
	else if (*spec == 'd' || *spec == 'i')
		error_check = apply_int(ap, info, print_len);
	else if (*spec == 'u')
		error_check = apply_unint(ap, info, print_len);
	else if (*spec == 'x' || *spec == 'X')
		error_check = apply_hex(ap, spec, info, print_len);
	else
		return (0);
	if (!error_check)
		return (0);
	return (spec);
}
