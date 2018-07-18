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

int		ft_exec(char *name, char **argv, char **envp, pid_t *pid)
{
	pid_t	pidl;
	int		ret;

	ret = -1;
	if (!(pidl = fork()))
	{
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
