/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 20:30:00 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/16 17:36:19 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_math.h"
#include "ft_printf.h"

int			expr_cond_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int	efail;

	(void)iterf;
	if (ft_strequ(ast->name, "&&") && !(*(EXPRT *)op[0]))
		return ((*(EXPRT *)res = 0));
	else if (ft_strequ(ast->name, "||") && *(EXPRT *)op[0])
		return (!(*(EXPRT *)res = 1));
	if ((efail = ft_astiter(ast->right, (void *)op[1], iterf)))
		return (efail);
	if (ft_strequ(ast->name, "&&"))
		*(EXPRT *)res = (*(EXPRT *)op[0] && *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, "||"))
		*(EXPRT *)res = (*(EXPRT *)op[0] || *(EXPRT *)op[1]);
	return (0);
}

int			expr_equ_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	EXPRT		efail;
	char		*tmp;
	t_exprdata	*data;

	(void)iterf;
	if (ast->left->type != ast->left->cmd_offset
			|| !ast->left->args || ast->left->args->argc > 1
			|| !ft_strmatch_x(ast->left->name, EXPR_DLM_VARV))
		return (EXPR_LVALREQ);
	data = (t_exprdata *)(ast->data ? ast->data : NULL);
	if (*ast->name == '=')
		*(EXPRT *)res = *(EXPRT *)op[1];
	else
	{
		efail = (EXPRT)ft_atoll(ft_getenv(ast->left->name, *data->var_db));
		ft_memcpy(op[0], &efail, sizeof(EXPRT));
		if ((efail = (EXPRT)expr_arth_cb(ast, op, res, iterf)))
			return ((int)efail);
	}
	ft_setenv(ast->left->name, (tmp = ft_lltoa(*(EXPRT *)res)), data->var_db);
	free(tmp);
	return (0);
}

static int	expr_arth_cb2(t_ast *ast, void **op, void *res)
{
	if (*ast->name == '&')
		*(EXPRT *)res = ((*(EXPRT *)op[0]) & (*(EXPRT *)op[1]));
	else if (*ast->name == '|')
		*(EXPRT *)res = ((*(EXPRT *)op[0]) | (*(EXPRT *)op[1]));
	else if (*ast->name == '^')
		*(EXPRT *)res = ((*(EXPRT *)op[0]) ^ (*(EXPRT *)op[1]));
	else if (ft_strequ(ast->name, "<<") || ft_strequ(ast->name, "<<="))
		*(EXPRT *)res = ((*(EXPRT *)op[0]) << (*(EXPRT *)op[1]));
	else if (ft_strequ(ast->name, ">>") || ft_strequ(ast->name, ">>="))
		*(EXPRT *)res = (*(EXPRT *)op[0] >> *(EXPRT *)op[1]);
	return (0);
}

int			expr_arth_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	(void)iterf;
	if (*ast->name == '+')
		*(EXPRT *)res = (*(EXPRT *)op[0] + *(EXPRT *)op[1]);
	else if (*ast->name == '-')
		*(EXPRT *)res = (*(EXPRT *)op[0] - *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, "**"))
		*(EXPRT *)res = (EXPRT)ft_powl(*(EXPRT *)op[0], *(EXPRT *)op[1]);
	else if (*ast->name == '*')
		*(EXPRT *)res = (*(EXPRT *)op[0] * *(EXPRT *)op[1]);
	else if (*ast->name == '/' || *ast->name == '%')
	{
		if (!(*(EXPRT *)op[1]))
			return (EXPR_DIVZERO);
		if (*ast->name == '/')
			*(EXPRT *)res = (*(EXPRT *)op[0] / *(EXPRT *)op[1]);
		else
			*(EXPRT *)res = (*(EXPRT *)op[0] % *(EXPRT *)op[1]);
	}
	return (expr_arth_cb2(ast, op, res));
}

int			expr_comp_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	(void)iterf;
	if (ft_strequ(ast->name, "<="))
		*(EXPRT *)res = (*(EXPRT *)op[0] <= *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, ">="))
		*(EXPRT *)res = (*(EXPRT *)op[0] >= *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, "=="))
		*(EXPRT *)res = (*(EXPRT *)op[0] == *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, "!="))
		*(EXPRT *)res = (*(EXPRT *)op[0] != *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, "<"))
		*(EXPRT *)res = (*(EXPRT *)op[0] < *(EXPRT *)op[1]);
	else if (ft_strequ(ast->name, ">"))
		*(EXPRT *)res = (*(EXPRT *)op[0] > *(EXPRT *)op[1]);
	return (0);
}
