/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_resolve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:58:07 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:58:27 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_b(int size, t_list **list_a, t_list **list_b)
{
	int		j;
	int		i;

	i = 0;
	while (i++ < 2)
	{
		j = 0;
		if (find_pos(find_min(*list_a), *list_a) < size / 2)
			j = 1;
		while ((*list_a)->content != find_min(*list_a))
		{
			if (j)
				ra(list_a, 0);
			else
				rra(list_a, 0);
		}
		pb(list_a, list_b, 0);
	}
}

void	short_resolve(t_list **list_a)
{
	int		size;
	t_list	*list_b;

	list_b = 0;
	size = find_size(*list_a);
	if (is_sort(*list_a))
		return ;
	if (size > 3)
		push_b(size, list_a, &list_b);
	while (!is_sort(*list_a))
	{
		if ((*list_a)->content >= find_max(*list_a, -2147483648))
			ra(list_a, 0);
		else if ((*list_a)->content > (*list_a)->next->content)
			sa(*list_a, 0);
		else
			ra(list_a, 0);
	}
	if (size > 3)
	{
		pa(list_a, &list_b, 0);
		pa(list_a, &list_b, 0);
	}
}
