/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:21:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/18 17:47:11 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <sys/wait.h>
#include <sys/types.h>

int		fnd_numbg(void)
{
	int	i;

	i = -1;
	while (++i < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[i] && g_shell->bgproc[i]->pid == g_shell->curpid)
			return (g_shell->bgproc[i]->x);
	}
	return (-1);
}

int		ft_exec(char *name, char **argv, char **envp, pid_t *pid)
{
	pid_t	pidl;
	int	ret;
	int	i;
	int	ret1;

	ret = -1;
	i = -1;
	if (!(pidl = fork()))
	{
		if (g_shell->c & (1 << 0))
		{
			if ((ret1 = fnd_numbg()) == -1)
				ft_exit(EXIT_FAILURE, "ERROR FND_NUMBG\n");
			ft_printf("[%d] %d\n", fnd_numbg(), getpid());
		}
		execve(name, argv, envp);
		exit(126);
	}
	else if (pidl == -1)
		return (-1);
	if (pid)
		*pid = pidl;
	if (!g_shell->dontwait)
		wait(&ret);
	return (WEXITSTATUS(ret));
}

char	*ft_getcwd(char *pwd, size_t size)
{
	static char	spwd[2048];

	if (!pwd)
		return (getcwd(spwd, 2048));
	return (getcwd(ft_bzero(pwd, size), size));
}
