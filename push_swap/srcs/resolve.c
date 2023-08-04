/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:21:21 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 19:51:14 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_max(t_list **list_a, t_list **list_b, int m, t_info *info)
{
	int	f;

	f = 0;
	if ((*list_b)->content < m)
	{
		while ((*list_b)->content != m)
		{
			if ((*list_b)->next->content == m)
			{
				sb(*list_b, 0);
				pa(list_a, list_b, 0);
				f = 1;
				break ;
			}
			if (info->flags == 1)
				rb(list_b, 0);
			else
				rrb(list_b, 0);
		}
	}
	if (!f)
		pa(list_a, list_b, 0);
}

static void	push_a2(t_list **list_b, t_data *data)
{
	data->flags_b1 = 0;
	data->flags_b2 = 0;
	data->max_b1 = find_max(*list_b, -2147483648);
	data->max_b2 = find_max(*list_b, data->max_b1);
	data->pos_b1 = find_pos(data->max_b1, *list_b);
}

static void	push_a(t_list **list_a, t_list **list_b, t_info *info, t_data *data)
{
	while (info->size_b)
	{
		push_a2(list_b, data);
		if (data->pos_b1 < info->size_b / 2)
			data->flags_b1 = 1;
		if (data->max_b2 != -2147483648)
		{
			data->pos_b2 = find_pos(data->max_b2, *list_b);
			if (data->pos_b2 < info->size_b / 2)
				data->flags_b2 = 1;
		}
		info->flags = data->flags_b1;
		if (data->max_b2 != -2147483648 && data->flags_b1 == data->flags_b2
			&& ((data->pos_b1 > data->pos_b2 && data->flags_b1)
				|| (data->pos_b1 < data->pos_b2 && !data->flags_b1)))
		{
			push_max(list_a, list_b, data->max_b2, info);
			push_max(list_a, list_b, data->max_b1, info);
			sa(*list_a, 0);
			info->size_b--;
		}
		else
			push_max(list_a, list_b, data->max_b1, info);
		info->size_b--;
	}
}

static void	opti_rotation(int tmp, t_list **list_a, t_list **list_b,
				t_info **info)
{
	while (tmp && (*info)->size_a > 2)
	{
		if ((*list_a)->content <= (*info)->pivot)
		{
			pb(list_a, list_b, 0);
			if ((*list_b)->content < find_median(*list_b, (*info)->size_b)
				&& (*info)->size_b > 1)
			{
				if ((*list_a)->content > (*info)->pivot)
					rr(list_a, list_b, 0);
				else
					rb(list_b, 0);
			}
			(*info)->size_b++;
			(*info)->size_a--;
		}
		else
			ra(list_a, 0);
		tmp--;
	}
}

int	resolve(t_list **list_a, t_info *info)
{
	int		tmp;
	t_data	*data;
	t_list	*list_b;

	list_b = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (is_sort(*list_a))
		return (1);
	info->size_a = find_size(*list_a);
	info->size_b = 0;
	while (info->size_a > 2)
	{
		info->pivot = find_median(*list_a, info->size_a);
		tmp = info->size_a;
		opti_rotation(tmp, list_a, &list_b, &info);
	}
	pb(list_a, &list_b, 0);
	pb(list_a, &list_b, 0);
	info->size_b += 2;
	push_a(list_a, &list_b, info, data);
	free(data);
	return (1);
}
