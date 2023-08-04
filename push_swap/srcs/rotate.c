/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:57:49 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:57:59 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **list_a, int p)
{
	t_list	*tmp;
	t_list	*cp;

	if (!(*list_a) || !((*list_a)->next))
		return ;
	tmp = *list_a;
	cp = (*list_a)->next;
	while ((*list_a)->next)
		*list_a = (*list_a)->next;
	(*list_a)->next = tmp;
	tmp->next = NULL;
	*list_a = cp;
	if (p != 1)
		write(1, "ra\n", 3);
}

void	rb(t_list **list_b, int p)
{
	t_list	*tmp;
	t_list	*cp;

	if (!(*list_b) || !(*list_b)->next)
		return ;
	tmp = *list_b;
	cp = (*list_b)->next;
	while ((*list_b)->next)
		*list_b = (*list_b)->next;
	(*list_b)->next = tmp;
	tmp->next = NULL;
	*list_b = cp;
	if (p != 1)
		write(1, "rb\n", 3);
}

void	rr(t_list **list_a, t_list **list_b, int p)
{
	ra(list_a, 1);
	rb(list_b, 1);
	if (p != 1)
		write(1, "rr\n", 3);
}
