/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 09:47:27 by jlim              #+#    #+#             */
/*   Updated: 2021/06/24 15:42:59 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	print_error(int err_num)
{
	write(2, "Error\n", 6);
	if (err_num == 1)
		write(2, ERR1, ft_strlen(ERR1));
	else if (err_num == 2)
		write(2, ERR2, ft_strlen(ERR2));
	else if (err_num == 3)
		write(2, ERR3, ft_strlen(ERR3));
	else if (err_num == 4)
		write(2, ERR4, ft_strlen(ERR4));
	else if (err_num == 5)
		write(2, ERR5, ft_strlen(ERR5));
	else if (err_num == 6)
		write(2, ERR6, ft_strlen(ERR6));
	else if (err_num == 7)
		write(2, ERR7, ft_strlen(ERR7));
	else if (err_num == 8)
		write(2, ERR8, ft_strlen(ERR8));
	else if (err_num == 9)
		write(2, ERR9, ft_strlen(ERR9));
	return (err_num);
}

int	main(int ac, char **av)
{
	t_map	*map;
	int		err_num;

	map = NULL;
	err_num = 0;
	if (ac != 2)
		err_num = 1;
	if (!err_num)
		err_num = parse(&map, av[1]);
	if (!err_num)
		err_num = play(map);
	map_clear(&map);
	if (err_num)
		return (print_error(err_num));
	return (0);
}
