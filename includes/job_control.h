/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:59:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 20:35:49 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "shell.h"

# define MAX_BGPROC 21

typedef	enum		e_bgstat
{
	BG_RUN, BG_END, BG_KILL, BG_STOP
}					t_bgstat;

typedef struct		s_bgstats
{
	int				status;
	char			*message;
}					t_bgstats;

typedef struct		s_inffork
{
	int				x;
	pid_t			pid;
	char			sign;
	char			status[100];
	char			**cmd;
	unsigned int	modif : 1;
}					t_inffork;

int					exec_cmd_background(t_ast *ast, void *res, t_iterf *iterf);
int					exec_btin_bin(t_ast *ast, void *res, t_iterf *iterf);
int					handle_bgstat(pid_t pid, int status);
int					handle_bgproc(pid_t pid_fork,
									char **cmd,
									int status,
									int opt);
int					check_bgend(void);
int					end_status(char *str);
void				print_cmd_args(char **tab);
void				print_cmd_args2(char **tab);
char				**ret_args(t_ast *ast);
t_ast				*ret_astargs(t_ast *ast);
void				handle_bgsign(t_list *elem, int opt);
void				handle_pgid(void);
void				freelst_bg(void);
void				del(void *content, size_t size);
void				sign_child(int sign);
t_list				*ret_sign(int opt);
void				debug_sign();

#endif
