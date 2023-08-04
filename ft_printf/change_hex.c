/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:50:09 by jlim              #+#    #+#             */
/*   Updated: 2021/06/08 15:54:00 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_len(size_t num)
{
	int	idx;

	idx = 0;
	while (num >= 16)
	{
		num /= 16;
		idx++;
	}
	return (idx);
}

char	*change_hex(size_t num, const char *spec)
{
	char	*hex;
	char	*result;
	int		idx;

	if (!(result = (char *)ft_calloc(sizeof(char), 13)))
		return (0);
	if (*spec == 'x' || *spec == 'p')
		hex = "0123456789abcdef";
	else if (*spec == 'X')
		hex = "0123456789ABCDEF";
	idx = check_len(num);
	while (idx >= 0)
	{
		result[idx] = hex[num % 16];
		num = num / 16;
		idx--;
	}
	return (result);
}
