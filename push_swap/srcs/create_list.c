/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:05:22 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:32:11 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_dup(t_list *list)
{
	int		n;
	t_list	*tmp;

	n = list->content;
	tmp = list;
	while (list->next)
	{
		list = list->next;
		if (list->content == n)
			return (0);
	}
	if (tmp->next)
		if (!(check_dup(tmp->next)))
			return (0);
	return (1);
}

static t_list	*fill_list(t_list *list, long long **val, char **av)
{
	int	i;
	int	*int_val;

	i = 0;
	int_val = (int *)malloc(sizeof(int) * arg_count(av));
	if (!int_val)
		return (NULL);
	while (i < arg_count(av))
	{
		int_val[i] = (int)val[0][i];
		add_link(&list, int_val[i]);
		i++;
	}
	free(*val);
	free(int_val);
	return (list);
}

t_list	*create_list(char **av)
{
	t_list		*list;
	long long	*val;

	list = NULL;
	if (!check_arg(av, &val))
		return (NULL);
	list = fill_list(list, &val, av);
	if (!(check_dup(list)))
	{
		free_list(list);
		return (NULL);
	}
	return (list);
}
