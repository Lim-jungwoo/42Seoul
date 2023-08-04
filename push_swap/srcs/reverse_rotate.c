/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:57:30 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:57:43 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **list_a, int p)
{
	t_list	*tmp;
	t_list	*cp;

	if (!(*list_a) || !(*list_a)->next)
		return ;
	tmp = *list_a;
	cp = *list_a;
	while (tmp->next)
	{
		if (tmp->next->next)
			cp = cp->next;
		tmp = tmp->next;
	}
	cp->next = NULL;
	tmp->next = *list_a;
	*list_a = tmp;
	if (p != 1)
		write(1, "rra\n", 4);
}

void	rrb(t_list **list_b, int p)
{
	t_list	*tmp;
	t_list	*cp;

	if (!(*list_b) || !(*list_b)->next)
		return ;
	tmp = *list_b;
	cp = *list_b;
	if (!(*list_b))
		return ;
	while (tmp->next)
	{
		if (tmp->next->next)
			cp = cp->next;
		tmp = tmp->next;
	}
	cp->next = NULL;
	tmp->next = *list_b;
	*list_b = tmp;
	if (p != 1)
		write(1, "rrb\n", 4);
}

void	rrr(t_list **list_a, t_list **list_b, int p)
{
	rra(list_a, 1);
	rrb(list_b, 1);
	if (p != 1)
		write(1, "rrr\n", 4);
}
