/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:21:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/05 06:56:43 by jraymond         ###   ########.fr       */
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
		exit(-1);
	}
	else if (pidl)
	{
		if (pid)
			*pid = pidl;
		wait(&ret);
	}
	return (ret == 65280 ? -1 : ret);
}

char	*ft_getcwd(char *pwd, size_t size)
{
	static char	spwd[2048];

	if (!pwd)
		return (getcwd(spwd, 2048));
	return (getcwd(ft_bzero(pwd, size), size));
}
