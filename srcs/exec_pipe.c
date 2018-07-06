/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 05:44:20 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/06 15:20:46 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "errno.h"
#include "string.h"

int		pipe_error(int error)
{
	if (error == 1)
		ft_putstr_fd("21sh: error fork\n", 2);
	else if (error == 2)
		ft_putstr_fd("21sh: error pipe\n", 2);
	return (-1);
}

int		pipe_duplicate(t_ast *ast)
{
	pid_t	pid;
	int		pidfd[2];
	char	buff[1024];

	if (pipe(pidfd) == -1)
		return (pipe_error(2));
	if ((pid = fork()) == -1)
		return (pipe_error(1));
	if (pid != 0)
	{
		ast = ast->left;
		ft_astresolver(ast, 0);
		ft_getfullpath(ast->name, g_shell->paths, buff, 1024);
		close(pidfd[0]);
		if (dup2(pidfd[1], 1) == -1)
		{
			ft_printf("FAIL dup\n");
			ft_printf("ERROR: %s\n", strerror(errno));
			exit(0);
		}
		if (execve(buff, ast->args->argv, g_shell->envp) == -1)
		{
			ft_printf("FAIL_fils execve\n");
			ft_printf("ERROR: %s\n", strerror(errno));
			exit(0);
		}
	}
	else
	{
		wait(NULL);
		ast = ast->right;
		ft_astresolver(ast, 0);
		ft_getfullpath(ast->name, g_shell->paths, buff, 1024);
		close(pidfd[1]);
		if (dup2(pidfd[0], 0) == -1)
		{
			ft_printf("FAIL dup\n");
			ft_printf("ERROR: '%s'\n", strerror(errno));
			exit(0);
		}
		if (execve(buff, ast->args->argv, g_shell->envp) == -1)
		{
			ft_printf("FAIL_pere execve\n");
			ft_printf("ERROR: %s\n", strerror(errno));
			exit(0);
		}
	}
	return (0);
}

int		exec_pipe(t_ast *ast, void *res)
{
	pid_t			pidl;
	/*int				status;
	struct rusage	ru;*/
	
	(void)res;
	if ((pidl = fork()) == -1)
		return (pipe_error(1));
	if (!pidl)
		pipe_duplicate(ast);
	else
		wait(NULL);
	return (0);
}	
