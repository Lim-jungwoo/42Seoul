/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:00:52 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:01:44 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	compare(char *line, t_list **list_a, t_list **list_b)
{
	if (!(ft_strcmp(line, "ra")))
		ra(list_a, 1);
	else if (!(ft_strcmp(line, "rb")))
		rb(list_b, 1);
	else if (!(ft_strcmp(line, "rr")))
		rr(list_a, list_b, 1);
	else if (!(ft_strcmp(line, "sa")))
		sa(*list_a, 1);
	else if (!(ft_strcmp(line, "sb")))
		sb(*list_b, 1);
	else if (!(ft_strcmp(line, "ss")))
		ss(*list_a, *list_b, 1);
	else if (!(ft_strcmp(line, "rra")))
		rra(list_a, 1);
	else if (!(ft_strcmp(line, "rrb")))
		rrb(list_b, 1);
	else if (!(ft_strcmp(line, "rrr")))
		rrr(list_a, list_b, 1);
	else if (!(ft_strcmp(line, "pa")))
		pa(list_a, list_b, 1);
	else if (!(ft_strcmp(line, "pb")))
		pb(list_a, list_b, 1);
	else
		return (0);
	return (1);
}

int	checker(t_list **list_a, t_list **list_b)
{
	int		ret;
	char	*line;

	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		if (ret == -1)
		{
			free(line);
			return (0);
		}
		if (!(compare(line, list_a, list_b)))
		{
			free(line);
			return (0);
		}
		free(line);
		ret = get_next_line(0, &line);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		ret;
	t_list	*list_a;
	t_list	*list_b;

	if (ac < 2)
		return (0);
	list_a = create_list(av);
	if (!list_a)
		return (err_free_list(list_a));
	ret = checker(&list_a, &list_b);
	if (ret == 0)
		return (err_free_list(list_a));
	if (list_a && is_sort(list_a) && !list_b)
		write(1, "OK\n", 3);
	else
		write(2, "KO\n", 3);
	if (list_b)
		free_list(list_b);
	free_list(list_a);
	return (0);
}
