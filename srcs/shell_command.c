/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_callbacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:18:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/19 16:42:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "pipe.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "ft_mem.h"
#include <sys/stat.h>
#include <sys/wait.h>

// LE TRUCK QUI GERE LES ERREURS -> ft_getpaths.c

static int	is_file(const char *name)
{
	struct stat	st;

	if (stat(name, &st))
		return (0);
	return (S_ISREG(st.st_mode));
}

int			shell_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		ret;
	char	buff[1024];

	(void)op;
	if ((ret = ft_astresolver(ast, (t_expf *)iterf->data)))
		return ((*(int *)res = 1) ? ret : ret);
	if ((*(int *)res = execbuiltin(ast->name, ast->args)) != -1)
		return (g_shell->running ? 0 : SH_EXIT);
	if (!ast || !ast->name || !*ast->name)
		return (0);
	if ((ret = ft_getfullpath(ast->name, g_shell->paths, buff, 1024)) != SH_OK)
	{
		ft_printshret(ret, ast->name);
		*(int *)res = (ret == SH_ADENIED ? 126 : 127);
		return (0);
	}
	if (!is_file(buff) && (*(int *)res = 128))
		ft_printshret(SH_NFILE, ast->name);
	else if ((*(int *)res = ft_exec(buff, ast->args->argv, g_shell->envp,
					&g_shell->curpid)) == -1)
		return (SH_FORKFAIL);
	if (*(int *)res == 126)
		ft_printshret(SH_EXECERR, ast->name);
	return (0);
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
	int		fd[2];
	int		efail;

	efail = 0;
	if (pipe(fd) == -1)
		return (SH_PIPFAIL);
	if ((pid = fork()) == -1)
		return (SH_FORKFAIL);
	else if (!pid)
	{
		efail = ft_astiter(head, res, iterf);
		close(fd[0]);
		ft_printf_fd(fd[1], "%.*r\n%.*r", sizeof(int), &efail,
				sizeof(int), res);
		close(fd[1]);
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
	else
		efail = lists_subshell(head, res, iterf);
	ft_astdel(&head);
	return (efail);
}
