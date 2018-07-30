/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:36:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/19 19:42:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include "ft_printf.h"

static pid_t	new_fork(t_ast *ast, void *res, t_iterf *iterf, int fd[2])
{
	pid_t	pid;
	int		ir;

	if (!ast || !ast->name)
		return (-1);
	ir = (ast == ast->parent->right ? 1 : 0);
	if (!(pid = fork()))
	{
		close(fd[ir]);
		dup2(fd[!ir], !ir);
		ft_astiter(ast, res, iterf);
		close(fd[!ir]);
		exit(*(int *)res);
	}
	return (pid);
}

int				shell_pipe_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		fd[2];
	pid_t	pidl;
	pid_t	pidr;
	int		leftres;
	int		rightres;

	(void)op;
	leftres = 0;
	if (pipe(fd) == -1)
		return (SH_PIPFAIL);
	if ((pidr = new_fork(ast->right, &rightres, iterf, fd)) == -1)
		return (SH_FORKFAIL);
	if ((pidl = new_fork(ast->left, &leftres, iterf, fd)) == -1)
		return (SH_FORKFAIL);
	close(fd[1]);
	close(fd[0]);
	waitpid(pidl, NULL, 0);
	waitpid(pidr, res, 0);
	*(int *)res >>= 8;
	return (0);
}

int				shell_andor_seco_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf)
{
	g_shell->exitcode = *(int *)op[0];
	if (*ast->name == '&')
	{
		if (*(int *)op[0] == 0)
			ft_astiter(ast->right, res, iterf);
		else
			*(int *)res = *(int *)op[0];
	}
	else if (*ast->name == '|')
	{
		if (*(int *)op[0] != 0)
			ft_astiter(ast->right, res, iterf);
		else
			*(int *)res = *(int *)op[0];
	}
	else if (*ast->name == ';')
	{
		if (ast->right && ast->right->name)
			*(int *)res = *(int *)op[1];
		else if (ast->left && ast->left->name)
			*(int *)res = *(int *)op[0];
	}
	return (0);
}

int				shell_bckgrnd_cb(t_ast *ast, void **op, void *res,
							t_iterf *iterf)
{
	(void)iterf;
	(void)op;
	if (*ast->name == '&')
	{
		if (exec_cmd_background(ast, res, iterf) != 0)
			return (SH_FORKFAIL);
	}
	return (0);
}
