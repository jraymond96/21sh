/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_btin_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:37:15 by jraymond          #+#    #+#             */
/*   Updated: 2018/08/01 14:35:17 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>
#include <sys/stat.h>

static int	is_file(const char *name)
{
	struct stat	st;

	if (stat(name, &st))
		return (0);
	return (S_ISREG(st.st_mode));
}

int			exec_btin_bin(t_ast *ast, void *res, t_iterf *iterf)
{
	int		ret;
	char	buff[1024];

	if ((ret = ft_astcresolver(ast, (t_expf *)iterf->data)))
		return ((*(int *)res = 1) ? ret : ret);
	if (!ast || !ast->cname || !*ast->cname)
		return (0);
	if ((*(int *)res = execbuiltin(ast->cname, ast->cargs)) != -1)
		return (g_shell->running ? 0 : SH_EXIT);
	if ((ret = ft_getfullpath(ast->cname, g_shell->paths, buff, 1024)) != SH_OK)
	{
		ft_printshret(ret, ast->cname);
		*(int *)res = (ret == SH_ADENIED ? 126 : 127);
		return (0);
	}
	if (!is_file(buff) && (*(int *)res = 128))
		ft_printshret(SH_NFILE, ast->cname);
	else if ((*(int *)res = execve(buff, ast->cargs->argv, g_shell->envp)) == -1)
		ft_printshret(SH_EXECERR, ast->cname);
	return (0);
}
