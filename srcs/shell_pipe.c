/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 20:36:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/12 22:38:45 by mmerabet         ###   ########.fr       */
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
/*
int	shell_pipe_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		fd[2];
	int		leftres;
	pid_t	pidl;

	(void)op;
	leftres = 0;
	if (pipe(fd) == -1 && (*(int *)res = 1))
		return (SH_PIPFAIL);
	if ((pidl = fork()) == -1)
		return (SH_FORKFAIL);
	else if (!pidl)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		ft_astiter(ast->left, &leftres, iterf);
		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_astiter(ast->right, res, iterf);
		close(fd[1]);
		waitpid(pidl, NULL, 0);
	}
	return (0);
}*/
