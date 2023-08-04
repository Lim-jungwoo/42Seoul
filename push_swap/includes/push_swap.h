/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:59:06 by jlim              #+#    #+#             */
/*   Updated: 2021/09/30 13:01:17 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}					t_list;

typedef struct s_info
{
	int				pivot;
	int				size_b;
	int				size_a;
	int				flags;
}					t_info;

typedef struct s_data
{
	int				max_b1;
	int				max_b2;
	int				flags_b1;
	int				flags_b2;
	int				pos_b1;
	int				pos_b2;
}					t_data;

int					resolve(t_list **list_a, t_info *info);

int					is_sort(t_list *list_a);
int					find_size(t_list *list);
int					find_max(t_list *list, int skip);
int					find_min(t_list *list);
int					find_pos(int n, t_list *list);

void				short_resolve(t_list **list_a);

int					find_median(t_list *list_b, int size);

void				add_link(t_list **list, int n);
int					err_free_list(t_list *list);
void				free_list(t_list *list);
int					free_all(t_list *list, t_info *info);

void				sa(t_list *list_a, int p);
void				sb(t_list *list_b, int p);
void				ss(t_list *list_a, t_list *list_b, int p);
void				pa(t_list **list_a, t_list **list_b, int p);
void				pb(t_list **list_a, t_list **list_b, int p);
void				ra(t_list **list_a, int p);
void				rb(t_list **list_b, int p);
void				rr(t_list **list_a, t_list **list_b, int p);
void				rra(t_list **list_a, int p);
void				rrb(t_list **list_b, int p);
void				rrr(t_list **list_a, t_list **list_b, int p);

t_list				*create_list(char **av);

int					arg_count(char **av);
int					check_arg(char **av, long long **val);

#endif
