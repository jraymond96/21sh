/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 19:45:28 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/24 18:12:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <sys/wait.h>

#include "ft_printf.h"
#include <fcntl.h>

static int		check_cond(t_ast *ast, int type)
{
	if (type)
	{
		if (!ast->parent || !ast->parent->name
				|| !ft_strequ(ast->parent->name, "|"))
			return (1);
		else if (ft_strequ(ast->left->name, "|"))
			return (1);
		return (0);
	}
	if (!ast)
		return (0);
	if (ast->type == TK_REDIR && ft_strmatch(ast->name, "*<*"))
		return (1);
	else if (check_cond(ast->left, 0) || check_cond(ast->right, 0))
		return (1);
	return (0);
}

static pid_t	son_fork(pid_t pgrp, int fd[3], t_ast *ast, t_iterf *iterf)
{
	int	ir;
	int	pid;
	int	res;

	ir = (ast == ast->parent->right ? 1 : 0);
	if (!(pid = fork()))
	{
		setpgid(0, (!pgrp ? 0 : pgrp));
		close(fd[ir]);
		if (!fd[2])
			dup2(fd[!ir], !ir);
		g_shell->bits |= (1 << 1);
		ft_astiter(ast, &res, iterf);
		close(fd[!ir]);
		exit(res);
	}
	return (pid);
}

static pid_t	new_fork(t_ast *ast, t_iterf *iterf, int fd[3])
{
	pid_t			pid;
	int				ir;
	short			a;
	static pid_t	pgrp;

	ir = (ast == ast->parent->right ? 1 : 0);
	a = !(pgrp) ? 1 : 0;
	if (ir && check_cond(ast, 0))
		fd[2] = 1;
	if ((g_shell->bits & (1 << 2)))
		pgrp = getpgrp();
	pid = son_fork(pgrp, fd, ast, iterf);
	setpgid(pid, (!pgrp ? (pgrp = pid) : pgrp));
	if (!(g_shell->bits & (1 << 2)) && a)
		tcsetpgrp(0, pgrp);
	g_shell->curpid = pgrp;
	if (!ir && ast->type != TK_PIPE)
		pgrp = 0;
	return (pid);
}

static int		exec_left(int fd[3], pid_t pids[2], t_ast *ast, t_iterf *iterf)
{
	int	m;
	int	res;

	if (!fd[2] && check_cond(ast, 1))
	{
		if ((pids[0] = new_fork(ast->left, iterf, fd)) == -1)
			if (!close(fd[0]) && !close(fd[1]))
				return (SH_FORKFAIL);
		if (!fd[2])
			waitpid(pids[0], NULL, WUNTRACED);
	}
	else if (!fd[2])
	{
		m = dup(1);
		close(fd[0]);
		dup2(fd[1], 1);
		g_shell->bits |= (1 << 1);
		ft_astiter(ast->left, &res, iterf);
		dup2(m, 1);
		g_shell->bits &= ~(1 << 1);
	}
	return (0);
}

int				shell_pipe_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		fd[3];
	pid_t	pids[2];

	(void)op;
	ft_bzero(fd, sizeof(int) * 3);
	if (pipe(fd) == -1)
		return (SH_PIPFAIL);
	if ((pids[1] = new_fork(ast->right, iterf, fd)) == -1)
		if (!close(fd[0]) && !close(fd[1]))
			return (SH_FORKFAIL);
	if (exec_left(fd, pids, ast, iterf))
		return (SH_FORKFAIL);
	close(fd[0]);
	close(fd[1]);
	waitpid(pids[1], res, WUNTRACED);
	*(int *)res = WEXITSTATUS(*(int *)res);
	if (!(g_shell->bits & (1 << 2)))
		tcsetpgrp(0, g_shell->shellpid);
	return (0);
}
