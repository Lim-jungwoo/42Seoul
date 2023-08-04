/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:19:50 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:02:02 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	push_swap(t_list **list_a, t_info *info)
{
	if (find_size(*list_a) > 8)
	{
		if (!(resolve(list_a, info)))
			return (0);
	}
	else
		short_resolve(list_a);
	return (1);
}

int	main(int ac, char **av)
{
	t_list	*list_a;
	t_info	*info;

	if (ac < 2)
		return (0);
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	list_a = create_list(av);
	if (!list_a)
	{
		free(info);
		write(2, "Error\n", 6);
		return (0);
	}
	push_swap(&list_a, info);
	free_list(list_a);
	free(info);
	return (0);
}
