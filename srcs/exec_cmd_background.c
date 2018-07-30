/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_background.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:42:32 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 21:53:33 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

static int		g_pid;

int				error_bgproc(int i)
{
	if (i == 0)
		ft_printf_fd(2, "21sh: %s (%d)\n",
				ft_strshret(SH_MAXBGPROC), MAX_BGPROC);
	else if (i == 1)
		ft_exitf(EXIT_FAILURE, "21sh: Error Malloc\n");
	else if (i == 2)
		ft_exitf(EXIT_FAILURE, "21sh: Error Setpgid\n")
	return (-1);
}

t_inffork	*init_infproc(int x, pid_t pid, char **cmd)
{
	t_inffork	*new;

	if (!(new = (t_inffork *)ft_memalloc(sizeof(t_inffork))))
		return (NULL);
	new->x = x;
	new->pid = pid;
	new->cmd = ft_copyenv(cmd);
	new->sign = ' ';
	return (new);
}



static void	sign_handler(int sign)
{
	if (sign == SIGCHLD)
	{
		if (WIFSTOPPED(g_status))
			handle_bgstat(g_shell->lpidchange, BG_STOP);
		else if (WIFCONTINUED(g_status))
			handle_bgstat(g_shell->lpidchange, BG_RUN);
		else if (!WIFEXITED(g_status))
			handle_bgstat(g_shell->lpidchange, BG_KILL);
		else if (WIFEXITED(g_status))
			handle_bgstat(g_shell->lpidchange, BG_END);
	}
}

int			exec_cmd_background(t_ast *ast, void *res, t_iterf *iterf)
{
	pid_t		pid;
	t_inffork	inf;
	int			x;
	char		**args;

	ft_bzero(&inf, sizeof(t_inffork));
	if ((pid = fork()) == -1)
		return (SH_FORKFAIL);
	if (!pid)
	{
		if (setpgid(getpid(), 0) == -1)
			error_bgproc(2);
		if (ast->left->args->argv[0][0] == '(')
		{
			ft_printf("Handle &> (...)\n");
				return (0);
		}
		args = ret_args(ast);
		pid = getpid();
		if ((x = handle_bgproc(pid, args)) == -1)
			exit(126);
		ft_printf("[%d] %d\n", g_shell->bgproc[x]->x, pid);
		exec_btin_bin(ret_astargs(ast), res, iterf);
		exit(126);
	}
	else
	{
		g_pid = pid;
		handle_bgproc(pid, ret_args(ast));
		signal(SIGCHLD, sign_child);
		ft_astiter(ast->right, res, iterf);
	}
	return (0);
}
