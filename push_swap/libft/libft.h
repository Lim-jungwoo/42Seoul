/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:45:20 by jlim              #+#    #+#             */
/*   Updated: 2021/09/29 17:56:46 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>

void			*ft_memset(void *dest, int fill_value, size_t count);
void			*ft_bzero(void *dest, size_t count);
void			*ft_memcpy(void *dest, const void *src, size_t count);
void			*ft_memccpy(void *dest, const void *src, int c, size_t count);
void			*ft_memmove(void *dest, const void *src, size_t count);
void			*ft_memchr(const void *s, int c, size_t count);
int				ft_memcmp(const void *s1, const void *s2, size_t count);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_strchr(char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
long long		ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

int				ft_strcmp(const char *s1, const char *s2);
int				get_next_line(const int fd, char **line);
void			ft_putstr(char const *s);
void			ft_swap(int *a, int *b);
void			ft_putchar(char c);
#endif
