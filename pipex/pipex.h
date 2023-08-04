/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlim <jlim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 14:09:51 by jlim              #+#    #+#             */
/*   Updated: 2021/06/30 14:14:02 by jlim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define ERR1	"ARGUMENT ERROR"
# define ERR2	"MALLOC ERROR"
# define ERR3	"FORK ERROR"
# define ERR4	"ENVIRON ERROR"
# define ERR5	"COMMAND ERROR"
# define ERR6	"RIGHT ERROR"
# define ERR7	"FILE EXIST ERROR"
# define ERR8	"EXECVE ERROR"

typedef struct	s_cmd
{
	int		fd[2];
	char	**av;
	char	**cmd1;
	char	**cmd2;
	char	**env;
}				t_cmd;

void			print_error(int err_num);
void			print_error2(int err_num, char *s);

void			ft_pipe(t_cmd *arg);

int				ft_check_file(char *s);
int				ft_check_file_exist(char *s);
char			*ft_check_command(t_cmd *arg, int childpid);

char			**ft_get_env(char *s, char **env);

char			**ft_strsplit(char *s, char c);

size_t			ft_strlen(char *s);
int				ft_strichr(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, size_t n);

#endif
