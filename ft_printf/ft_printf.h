/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:13:45 by jlim              #+#    #+#             */
/*   Updated: 2021/06/09 16:32:46 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "./libft/libft.h"
# define ONLYDOT 2
# define DOTNUM 1
# define NODOT 0
# define YES 1
# define NO 0

typedef struct	s_info
{
	int	f_hyphen;
	int	f_zero;
	int	w_num;
	int	p_num;
	int	p_is;
	int	p_ast;
}				t_info;

int				ft_printf(const char *format, ...);
int				parse_arg(va_list *ap, const char *format);
void			init_info(t_info *info);
char			*check_info(va_list *ap, const char *spec, t_info *info);
const char		*check_spec(va_list *ap, const char *spec,
		t_info info, int *print_len);
int				print_char(const char *spec, char *str,
		t_info info, size_t len);
int				print_num(char *str, t_info info, int sign);
int				apply_percent(const char *spec, t_info info, int *print_len);
int				apply_char(va_list *ap, const char *spec,
		t_info info, int *print_len);
int				apply_str(va_list *ap, const char *spec,
		t_info info, int *print_len);
int				apply_pointer(va_list *ap, const char *spec,
		t_info info, int *print_len);
int				apply_int(va_list *ap, t_info info, int *print_len);
int				apply_unint(va_list *ap, t_info info, int *print_len);
int				apply_hex(va_list *ap, const char *spec,
		t_info info, int *print_len);
char			*change_hex(size_t num, const char *spec);

#endif
