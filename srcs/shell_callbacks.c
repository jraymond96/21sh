/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_callbacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 18:18:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/05 06:58:03 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_str.h"

int	shell_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		efail;
	int		ret;
	char	buff[1024];

	(void)op;
	(void)iterf;
	ret = 0;
	*buff = '\0';
	if ((efail = ft_astresolver(ast, iterf->resolve_first)))
		return (efail);
	ft_printf("COMMAND CALLBACK: '%s'\n", ast->name);
	if ((ret = execbuiltin(ast->name, ast->args) == -1))
		*(int *)res = 127;
	else
	{
		*(int *)res = ret;
		return (0);
	}
	ret = ft_getfullpath(ast->name, g_shell->paths, buff, 1024);
	if (*(int *)res == 127 && !*buff)
		ft_printf_fd(2, "21sh: %s: %s\n", ft_strshret(ret), ast->name);
	*(int *)res = ft_exec(buff, ast->args->argv, g_shell->envp,
				&g_shell->curpid);
	return (0);
}

int	shell_andor_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	ft_printf("AND OR CALLBACK: '%s'\n", ast->name);
	(void)op;
	(void)res;
	(void)iterf;
	return (0);
}

int	shell_seco_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	ft_printf("SEMI-COLON CALLBACK: '%s'\n", ast->name);
	if (ast->right && ast->right->name)
		*(int *)res = *(int *)op[1];
	(void)op;
	(void)res;
	(void)iterf;
	return (0);
}

int	shell_pipe_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	ft_printf("PIPE CALLBACK: '%s'\n", ast->name);
	(void)op;
	(void)res;
	(void)iterf;
	return (0);
}

int	shell_redir_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_list	*redirs;
	t_list	*it;
	int		efail;

	ft_printf("REDIR CALLBACK: '%s'\n", ast->name);
	redirs = list_redirections(&ast);
	shell_cmd_cb(ast, op, res, iterf);
	ft_printf("Command: '%s'\n", ast->name);
	it = redirs;
	while (it)
	{
		t_rdrctn *r = (t_rdrctn *)it->content;
		if ((efail = ft_resolver(r->names, 1)))
			return (efail);
		ft_printf("\tredirection: type:%s full:'%s' out:%d in:%d file:'%s'\n",
					typestr(r->type), r->str, r->fd_out, r->fd_in, r->names->argv[0]);
		it = it->next;
	}
	ft_lstdel(&redirs, content_delfunc);
	(void)op;
	(void)res;
	(void)iterf;
	return (0);
}
