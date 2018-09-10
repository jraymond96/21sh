/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:21:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 22:33:08 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_str.h"
#include "ft_list.h"
#include <unistd.h>
#include <sys/wait.h>

int		fork_father(pid_t pidl)
{
	t_list	*elem;
	int		ret;

	ret = 0;
	handle_bgproc(pidl, g_shell->curargs->argv, BG_RUN);
	elem = ft_lstend(g_shell->bgproc);
	waitpid(pidl, &ret, WUNTRACED);
	tcsetpgrp(0, getpid());
	signal(SIGCHLD, sign_child);
	if (WIFSTOPPED(ret))
	{
		handle_bgstat(pidl, BG_STOP);
		return (WSTOPSIG(ret));
	}
	if (g_shell->bgproc == elem)
		g_shell->bgproc = NULL;
	else
		elem->parent->next = NULL;
	ft_lstdelone(&elem, del);
	return (WEXITSTATUS(ret));
}

int		ft_exec(char *name, char **argv, char **envp, pid_t *pid)
{
	pid_t	pidl;

	signal(SIGCHLD, SIG_DFL);
	if (!(pidl = fork()))
	{
		handle_pgid();
		execve(name, argv, envp);
		exit(126);
	}
	else if (pidl == -1)
		return (-1);
	if (pid)
		*pid = pidl;
	return (fork_father(pidl));
}

char	*ft_getcwd(char *pwd, size_t size)
{
	static char	spwd[2048];

	if (!pwd)
		return (getcwd(spwd, 2048));
	return (getcwd(ft_bzero(pwd, size), size));
}
