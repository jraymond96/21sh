/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_background.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:42:32 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/19 17:26:27 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>

static int		g_pid;

int				error_bgproc(int i)
{
	if (i == 0)
		ft_exitf(EXIT_FAILURE, "21sh: %s (%d)\n", SH_MAXBGPROC, MAX_BGPROC);
	else if (i == 1)
		ft_exitf(EXIT_FAILURE, "21sh: error malloc\n");
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

int				handle_bgproc(pid_t  pid_fork, char **cmd)
{
	int			x;
	t_inffork	*new;

	x = -1;
	while (++x < (MAX_BGPROC - 1) && g_shell->bgproc[x])
		;
	if (x == (MAX_BGPROC - 1))
		return (error_bgproc(0));
	else
	{
		if (!(new = init_infproc((x + 1), pid_fork, cmd)))
			return (error_bgproc(1));
		g_shell->bgproc[x] = new;
		handle_bgstat(pid_fork, BG_RUN);
	}
	return (x);
}

void	sign_child(int sign)
{
	int	x;
	int	status;
	int	pid;

	x = -1;
	(void)sign;
	handle_bgstat(g_pid, BG_END);
	status = 0;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x])
		{
			pid = g_shell->bgproc[x]->pid;
			if (waitpid(pid, &status, WNOHANG) == pid)
			{
				if (WIFEXITED(status) == 1)
					ft_strcpy(g_shell->bgproc[x]->status, "Done");
				else
					ft_strcpy(g_shell->bgproc[x]->status, "Terminated");
			}
		}
	}
}

static void		sign_kill(int sign)
{
	(void)sign;
	if (g_shell->curpid)
	{
		kill(g_shell->curpid, SIGKILL);
		exit(0);
	}
}

void			sign_test(int sign)
{
	(void)sign;
	handle_bgstat(g_shell->curpid, BG_KILL);
}
/*
void	*waitstatus(void *x)
{
	int	pid;
	int	b_x;
	int	status;

	b_x = *(int *)x;
	pid = g_shell->bgproc[b_x]->pid;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == 1)
		ft_strcpy(g_shell->bgproc[b_x]->status, "Done");
	else
		ft_strcpy(g_shell->bgproc[b_x]->status, "Terminated");
	pthread_exit(NULL);
}*/

char	**ret_args(t_ast *ast)
{
	while (ast->left)
		ast = ast->left;
	return (ast->args->argv);
}

int			exec_cmd_background(t_ast *ast, void *res, t_iterf *iterf)
{
	pid_t		pid;
	t_inffork	inf;
	int			x;

	ft_bzero(&inf, sizeof(t_inffork));
	if ((pid = fork()) == -1)
		return (SH_FORKFAIL);
	g_shell->c |= (1 << 0);
	if (!pid)
	{
		g_shell->curpid = getpid();
		x = handle_bgproc(g_shell->curpid, ret_args(ast));
		if (signal(SIGINT, sign_kill) == SIG_ERR)
			ft_exit(EXIT_FAILURE,
					"21sh: failed to catch 'SIGKILL' signal. Exiting.");
//		ft_printf("[%d] %d\n", g_shell->bgproc[x]->x, g_shell->bgproc[x]->pid);
		ft_astiter(ast->left, res, iterf);
		exit(0);
	}
	else
	{
		g_shell->c &= (0 << 0);
		g_pid = pid;
		x = handle_bgproc(pid, ret_args(ast));
		if (signal(SIGCHLD, sign_child) == SIG_ERR)
			ft_exit(EXIT_FAILURE,
					"21sh: failed to catch 'SIGCHLD' signal. Exiting.");
		ft_astiter(ast->right, res, iterf);
	}
	return (0);
}
