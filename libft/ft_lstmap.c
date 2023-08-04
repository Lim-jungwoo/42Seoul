/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:09:24 by jlim              #+#    #+#             */
/*   Updated: 2021/02/18 13:57:54 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*head;

	curr = NULL;
	head = curr;
	while (lst)
	{
		curr = ft_lstnew((*f)(lst->content));
		if (!curr)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ft_lstadd_back(&head, curr);
		lst = lst->next;
	}
	return (head);
}
