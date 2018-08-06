/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_background.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:42:32 by jraymond          #+#    #+#             */
/*   Updated: 2018/08/01 22:59:14 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/jeremi/21sh/logger/incs/logger.h"

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_list.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

static int		g_pid;

static	int		error_bgproc(int i)
{
	if (i == 0)
		ft_printf_fd(2, "21sh: %s (%d)\n",
				ft_strshret(SH_MAXBGPROC), MAX_BGPROC);
	else if (i == 1)
		ft_exitf(EXIT_FAILURE, "21sh: Error Malloc\n");
	else if (i == 2)
		ft_exitf(EXIT_FAILURE, "21sh: Error Setpgid\n");
	return (-1);
}

static	void	sign_child(int sign)
{
	t_list	*elem;
	pid_t	pid;
	int		ret;

	elem = g_shell->bgproc;
	while (elem)
	{
		pid = ((t_inffork *)elem->content)->pid;
		if (sign == SIGCHLD && waitpid(pid, &ret, WNOHANG) == pid)
		{
//			if (WIFSTOPPED(ret))
//			{
//				handle_bgstat(pid, BG_STOP);
//				handle_bgsign(elem, 0);
//			}
			if (WIFCONTINUED(ret))
				handle_bgstat(pid, BG_RUN);
			else if (!WIFEXITED(ret))
				handle_bgstat(pid, BG_KILL);
			else if (WIFEXITED(ret))
				handle_bgstat(pid, BG_END);
			else
				ft_printf("Sign not\n"); // A retirer
		}
		elem = elem->next;
	}
}

int				exec_cmd_background(t_ast *ast, void *res, t_iterf *iterf)
{
	pid_t		pid;
	t_inffork	inf;
	char		**args;
	t_list		*elem;

	ft_bzero(&inf, sizeof(t_inffork));
	if ((pid = fork()) == -1)
		return (SH_FORKFAIL);
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		pid = getpid();
		if (setpgid(pid, 0) == -1)
			error_bgproc(2);
		log_trace("PID_S: %d | PGRP_S: %d\n", getpid(), getpgrp());
		if (ast->left->args->argv[0][0] == '(')
		{
			ft_printf("Handle &> (...)\n");
				return (0);
		}
		args = ret_args(ast);
		if (handle_bgproc(pid, args, BG_RUN) == -1)
			exit(126);
		elem = ft_lstend(g_shell->bgproc);
		ft_printf("[%d] %d\n", ((t_inffork *)elem->content)->x, pid);
		exec_btin_bin(ret_astargs(ast), res, iterf);
		exit(126);
	}
	else
	{
		g_pid = pid;
		log_trace("PID_F: %d | PGRP_F: %d\n", getpid(), getpgrp());
		handle_bgproc(pid, ret_args(ast), BG_RUN);
		signal(SIGCHLD, sign_child);
		ft_astiter(ast->right, res, iterf);
	}
	return (0);
}
