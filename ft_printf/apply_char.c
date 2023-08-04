/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:18:12 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 16:34:50 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		apply_percent(const char *spec, t_info info, int *print_len)
{
	int	len;

	if (info.p_num < 0 && info.p_ast == NO)
		return (0);
	len = 1;
	*print_len += print_char(spec, "%", info, len);
	return (1);
}

int		apply_char(va_list *ap, const char *spec,
		t_info info, int *print_len)
{
	char	c;
	int		len;

	c = va_arg(*ap, int);
	if ((info.p_is == DOTNUM) || info.f_zero == YES)
		return (0);
	len = 1;
	*print_len += print_char(spec, &c, info, len);
	return (1);
}

int		apply_str(va_list *ap, const char *spec, t_info info, int *print_len)
{
	char	*str;
	int		len;

	if ((str = va_arg(*ap, char *)) == NULL)
		str = "(null)";
	if (info.f_zero == YES || (info.p_is == DOTNUM && info.p_num < 0
				&& info.p_ast == NO))
		return (0);
	if ((info.p_is == DOTNUM && info.p_num == 0) || info.p_is == ONLYDOT)
	{
		(*print_len) += info.w_num;
		while (info.w_num--)
			write(1, " ", sizeof(char));
		return (1);
	}
	len = ft_strlen(str);
	if (info.p_is == DOTNUM && info.p_num > 0 && info.p_num < len)
		len = info.p_num;
	*print_len += print_char(spec, str, info, len);
	return (1);
}

int		apply_pointer(va_list *ap, const char *spec,
		t_info info, int *print_len)
{
	void	*ptr;
	char	*hex_ptr;
	char	*ox_hex;
	size_t	tmp;

	ptr = va_arg(*ap, void *);
	if ((info.p_is == DOTNUM) || (info.f_zero == YES))
		return (0);
	if (!(hex_ptr = change_hex((size_t)ptr, spec)))
		return (0);
	if (ptr == 0 && info.p_is == ONLYDOT)
		*hex_ptr = '\0';
	ox_hex = ft_strjoin("0x", hex_ptr);
	free(hex_ptr);
	tmp = ft_strlen(ox_hex);
	*print_len += print_char(spec, ox_hex, info, tmp);
	free(ox_hex);
	ox_hex = 0;
	return (1);
}
