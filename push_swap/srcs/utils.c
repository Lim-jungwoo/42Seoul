/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:58:52 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:59:58 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sort(t_list *list_a)
{
	while (list_a->next)
	{
		if (list_a->content > list_a->next->content)
			return (0);
		list_a = list_a->next;
	}
	return (1);
}

int	find_size(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	find_max(t_list *list, int skip)
{
	int	max;

	max = -2147483648;
	while (list->next)
	{
		if (list->content > max && list->content != skip)
			max = list->content;
		list = list->next;
	}
	if (list->content > max && list->content != skip)
		max = list->content;
	return (max);
}

int	find_min(t_list *list)
{
	int	min;

	min = 2147483647;
	while (list->next)
	{
		if (list->content < min)
			min = list->content;
		list = list->next;
	}
	if (list->content < min)
		min = list->content;
	return (min);
}

int	find_pos(int n, t_list *list)
{
	int	pos;

	pos = 0;
	while (list->content != n)
	{
		list = list->next;
		pos++;
	}
	return (pos);
}
