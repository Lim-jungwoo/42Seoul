/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:59:12 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 15:28:16 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*check_flag(char *spec, t_info *info)
{
	char	*flags;
	char	*tmp;
	char	*is_flag;

	tmp = spec;
	flags = "-0";
	while (tmp && ((is_flag = ft_strchr(flags, *tmp)) != 0))
	{
		if (tmp && (*is_flag) == '-')
			info->f_hyphen = YES;
		else if (tmp && (*is_flag) == '0')
			info->f_zero = YES;
		tmp++;
	}
	if (tmp == 0)
		return (0);
	return (tmp);
}

int		num_ast(va_list *ap, char **spec, int *error, t_info *info)
{
	int	wid_pre_num;

	wid_pre_num = 0;
	if (**spec && ft_isdigit(**spec))
	{
		while (ft_isdigit(**spec))
		{
			wid_pre_num = wid_pre_num * 10 + ((**spec) - '0');
			if (wid_pre_num > 2147483646)
				return (0);
			if (!(++(*spec)))
				return (0);
		}
	}
	else if (*spec && **spec == '*')
	{
		(*spec)++;
		if (info->p_is == DOTNUM)
			info->p_ast = YES;
		if ((wid_pre_num = va_arg(*ap, int)) > 2147483646)
			return (0);
	}
	*error = NO;
	return (wid_pre_num);
}

char	*check_width(va_list *ap, char *spec, t_info *info)
{
	int		wid_num;
	int		error;
	char	*tmp;

	tmp = spec;
	error = YES;
	wid_num = 0;
	if ((!(wid_num = num_ast(ap, &tmp, &error, info)))
			&& error == YES)
		return (0);
	if (wid_num < 0)
	{
		wid_num *= -1;
		info->f_hyphen = YES;
	}
	info->w_num = wid_num;
	return (tmp);
}

char	*check_precision(va_list *ap, char *spec, t_info *info)
{
	int		pre_num;
	int		error;
	char	*tmp;
	int		sign;

	tmp = spec;
	error = YES;
	sign = 1;
	pre_num = 0;
	if (*tmp == '.')
	{
		if (++tmp && (*tmp) == '-')
		{
			sign *= -1;
			tmp++;
		}
		if (*tmp && !(ft_isdigit(*tmp)) && (*tmp) != '*')
			info->p_is = ONLYDOT;
		else
			info->p_is = DOTNUM;
		if ((!(pre_num = num_ast(ap, &tmp, &error, info))) && error == YES)
			return (0);
	}
	info->p_num = (pre_num * sign);
	return (tmp);
}

char	*check_info(va_list *ap, const char *spec, t_info *info)
{
	char	*tmp;

	if (!ap || !spec)
		return (0);
	tmp = (char *)spec;
	if (!(tmp = check_flag(tmp, info)))
		return (0);
	if (!(tmp = check_width(ap, tmp, info)))
		return (0);
	if (!(tmp = check_precision(ap, tmp, info)))
		return (0);
	return (tmp);
}
