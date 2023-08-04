/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:23:14 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 13:25:39 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int err_num)
{
	if (err_num == 1)
		perror(ERR1);
	else if (err_num == 2)
		perror(ERR2);
	else if (err_num == 3)
		perror(ERR3);
	else if (err_num == 4)
		perror(ERR4);
	exit(1);
}

void	print_error2(int err_num, char *s)
{
	write(2, s, ft_strlen(s));
	write(2, " : ", 3);
	if (err_num == 5)
		perror(ERR5);
	else if (err_num == 6)
		perror(ERR6);
	else if (err_num == 7)
		perror(ERR7);
	else if (err_num == 8)
		perror(ERR8);
	exit(1);
}
