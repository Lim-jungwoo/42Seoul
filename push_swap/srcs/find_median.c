/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:18:59 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 18:19:00 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_tab(int *tab, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (tab[j] > tab[j + 1])
				ft_swap(&tab[j], &tab[j + 1]);
			j++;
		}
		i++;
	}
}

int	find_median(t_list *list, int size)
{
	int		i;
	int		*tab;

	i = 0;
	tab = malloc(sizeof(int) * size);
	while (list->next)
	{
		tab[i] = list->content;
		list = list->next;
		i++;
	}
	sort_tab(tab, size);
	i = 0;
	while (i < size / 2)
		i++;
	i = tab[i];
	free(tab);
	return (i);
}
