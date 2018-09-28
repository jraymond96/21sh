/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 21:52:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 20:43:51 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_io.h"
#include "ft_mem.h"

static int	shell_error_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	(void)op;
	(void)res;
	(void)iterf;
	*(t_ast **)res = ast;
	if (*ast->name == ';' || *ast->name == '\n')
		return (0);
	if (ast->u && !ft_astvalid(ast->right))
		return (SH_BADEXPR);
	else if (ast->u)
		return (0);
	if (!ft_astvalid(ast->left))
		return (SH_BADEXPR);
	else if (!ft_strequ(ast->name, "&")
			&& (ast->type != TK_REDIR || !ft_strchr(ast->name, '&'))
			&& !ft_astvalid(ast->right))
		return (SH_BADEXPR);
	return (0);
}

static int	shell_conditionals_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf)
{
	(void)op;
	(void)iterf;
	*(t_ast **)res = ast;
	if (*ast->name == 't' && (!ft_astvalid(ast->left)
				|| (*ast->left->name != 'i' && *ast->left->name != 'w')))
		return (SH_THENWCOND);
	else if ((*ast->name == 'i' || *ast->name == 'w')
			&& (!ft_astvalid(ast->parent) || *ast->parent->name != 't'))
		return (SH_CONDWTHEN);
	else if (*ast->name == 'e')
	{
		if (!ft_astvalid(ast->left) || (*ast->left->name != 'e'
					&& *ast->left->name != 't'
					&& *ast->left->name != 'i'))
			return (SH_ELSEWCOND);
	}
	return (0);
}

static t_astfunc	g_callbacks[] = {
	{"\\:=:&&:||:*[|&!,;\n@=1]:not", shell_error_cb, shell_error_cb, -2},
	{"*<<", shell_hdoc_cb, NULL, -1},
	{DLM_REDP, shell_error_cb, NULL, -2},
	{"then:if:while:else", shell_conditionals_cb, shell_conditionals_cb, -2}
};

static t_iterf		g_syntax_checker = {
	g_callbacks, sizeof(g_callbacks) / sizeof(t_astfunc), NULL, 0,
	sizeof(t_ast *)
};

int			check_syntax(t_ast *ast, t_expf *expf)
{
	t_ast	*res;
	int		ret;
	char	*err;

	res = NULL;
	g_syntax_checker.data = (void *)expf;
	if ((ret = ft_astiter(ast, &res, &g_syntax_checker)))
	{
		if ((err = ft_strshret(ret)))
			ft_printf_fd(2, "%s: %s: %s\n", g_shell->name, err,
					(res ? res->name : NULL));
	}
	return (ret);
}
