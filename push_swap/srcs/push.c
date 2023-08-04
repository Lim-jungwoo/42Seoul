/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:19:39 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:19:41 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **list_a, t_list **list_b, int p)
{
	t_list	*tmp;

	if (!(*list_b))
		return ;
	tmp = *list_b;
	*list_b = (*list_b)->next;
	tmp->next = *list_a;
	*list_a = tmp;
	if (p != 1)
		write(1, "pa\n", 3);
}

void	pb(t_list **list_a, t_list **list_b, int p)
{
	t_list	*tmp;

	if (!(*list_a))
		return ;
	tmp = *list_a;
	*list_a = (*list_a)->next;
	tmp->next = *list_b;
	*list_b = tmp;
	if (p != 1)
		write(1, "pb\n", 3);
}
