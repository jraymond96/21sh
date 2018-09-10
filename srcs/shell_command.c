/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:18:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 23:23:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "ft_mem.h"
#include <sys/stat.h>
#include <sys/wait.h>

static int	shell_cmd_cb2(char *buff, void *res, t_ast *ast, t_args *args)
{
	struct stat	st;
	int			i;

	if (!(i = (stat(buff, &st) ? 0 : S_ISREG(st.st_mode)))
			&& (*(int *)res = 128))
		ft_printshret(SH_NFILE, ast->cname);
	else if ((*(int *)res = ft_exec(buff, ast->cargs->argv, g_shell->envp,
					&g_shell->curpid)) == -1)
	{
		g_shell->curargs = args;
		return (SH_FORKFAIL);
	}
	if (*(int *)res == 126)
		ft_printshret(SH_EXECERR, ast->cname);
	g_shell->curargs = args;
	return (0);
}

int			shell_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		ret;
	char	buff[2048];
	t_args	*args;

	(void)op;
	if ((ret = ft_astcresolver(ast, ((t_allf *)iterf->data)->expf)))
		return ((*(int *)res = 1) ? ret : ret);
	if (!ast || !ast->cname || !*ast->cname)
		return (0);
	args = g_shell->curargs;
	g_shell->curargs = ast->cargs;
	if ((ret = check_function(ast, res, iterf)) != -1
			&& (g_shell->curargs = args))
		return (ret);
	if ((*(int *)res = execbuiltin(ast->cname, ast->cargs)) != -1
			&& (g_shell->curargs = args))
		return (g_shell->running ? 0 : SH_EXIT);
	if ((ret = ft_getfullpath(ast->cname, g_shell->paths, buff, 1024)) != SH_OK)
	{
		ft_printshret(ret, ast->cname);
		*(int *)res = (ret == SH_ADENIED ? 126 : 127);
		g_shell->curargs = args;
		return (0);
	}
	return (shell_cmd_cb2(buff, res, ast, args));
}

static int	in_parent(int fd[2], void *res)
{
	int		efail;
	char	*mem;

	wait(NULL);
	close(fd[1]);
	get_next_line(fd[0], &mem);
	ft_memcpy(&efail, mem, sizeof(int));
	ft_memdel((void **)&mem);
	get_next_line(fd[0], &mem);
	ft_memcpy(res, mem, sizeof(int));
	ft_memdel((void **)&mem);
	close(fd[0]);
	return (efail);
}

static int	lists_subshell(t_ast *head, void *res, t_iterf *iterf)
{
	pid_t	pid;
	pid_t	save;
	int		fd[2];
	int		efail;

	efail = 0;
	save = getpgrp();
	if (pipe(fd) == -1)
		return (SH_PIPFAIL);
	if ((pid = fork()) == -1)
		return (SH_FORKFAIL);
	else if (!pid)
	{
		handle_pgid();
		efail = ft_astiter(head, res, iterf);
		close(fd[0]);
		ft_printf_fd(fd[1], "%.*r\n%.*r", sizeof(int), &efail,
				sizeof(int), res);
		close(fd[1]);
		tcsetpgrp(0, save);
		ft_astdel(&head);
		exit(0);
	}
	return (in_parent(fd, res));
}

int			shell_lists_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	char	*ptr;
	char	tmp;
	int		efail;
	t_ast	*head;

	(void)op;
	ptr = ft_strend(ast->name);
	tmp = *ptr;
	*ptr = '\0';
	head = ft_lexer(ast->name + 1, ast->lexerf);
	*ptr = tmp;
	efail = 0;
	if (!head)
		return (0);
	if (*ast->name == '{')
		efail = ft_astiter(head, res, iterf);
	else if ((efail = lists_subshell(head, res, iterf)))
		efail = (efail == SH_EXIT ? 0 : efail);
	ft_astdel(&head);
	return (efail);
}
