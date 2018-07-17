/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_callbacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:18:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/16 17:35:44 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "pipe.h"
#include <sys/stat.h>

// LE TRUCK QUI GERE LES ERREURS -> ft_getpaths.c

int	is_file(const char *name)
{
	struct stat	st;

	if (stat(name, &st))
		return (0);
	return (S_ISREG(st.st_mode));
}

int	shell_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		ret;
	char	buff[1024];

	(void)op;
	if ((ret = ft_astresolver(ast, (t_expf *)iterf->data)))
		return ((*(int *)res = 1) ? ret : ret);
	if ((*(int *)res = execbuiltin(ast->name, ast->args)) != -1)
		return (0);
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

int	shell_andor_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	if (ft_strcmp(ast->name, "&&") == 0)
	{
		if (*(int *)op[0] == 0)
			ft_astiter(ast->right, res, iterf);
		else
			*(int *)res = *(int *)op[0];
	}
	else
	{
		if (*(int *)op[0] != 0)
			ft_astiter(ast->right, res, iterf);
		else
			*(int *)res = *(int *)op[0];
	}
	return (0);
}

int	shell_bckgrnd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
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
