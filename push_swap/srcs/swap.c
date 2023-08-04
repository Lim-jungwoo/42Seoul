/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:58:38 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:58:46 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list *list_a, int p)
{
	if (!list_a)
		return ;
	if (list_a->next)
	{
		ft_swap(&list_a->content, &list_a->next->content);
		if (p != 1)
			ft_putstr("sa\n");
	}
}

void	sb(t_list *list_b, int p)
{
	if (!list_b)
		return ;
	if (list_b->next)
	{
		ft_swap(&list_b->content, &list_b->next->content);
		if (p != 1)
			ft_putstr("sb\n");
	}
}

void	ss(t_list *list_a, t_list *list_b, int p)
{
	sa(list_a, 1);
	sb(list_b, 1);
	if (p != 1)
		ft_putstr("ss\n");
}
