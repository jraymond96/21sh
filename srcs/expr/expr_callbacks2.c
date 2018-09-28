/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_callbacks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 01:53:44 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:21:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_printf.h"

int	expr_incdec_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	char	*name;
	char	*tmp;
	EXPRT	itmp;

	(void)iterf;
	(void)op;
	if ((!ast->left || !ast->left->name) && (!ast->right || !ast->right->name))
		return (EXPR_LVALREQ);
	else if (ast->left && ast->left->name && ast->right && ast->right->name)
		return (EXPR_OPTMISS);
	name = (ast->u == 1 ? ast->right->name : ast->left->name);
	if (!ft_strmatch_x(name, EXPR_DLM_VARV))
		return (EXPR_LVALREQ);
	tmp = ft_getenv(name, *((t_exprdata *)ast->data)->var_db);
	itmp = (EXPRT)ft_atoll(ft_getenv(name,
				*((t_exprdata *)ast->data)->var_db));
	if (*ast->name == '+')
		*(EXPRT *)res = (ast->u == 1 ? ++itmp : itmp++);
	else
		*(EXPRT *)res = (ast->u == 1 ? --itmp : itmp--);
	ft_setenv(name, (tmp = ft_lltoa(itmp)),
			((t_exprdata *)ast->data)->var_db);
	free(tmp);
	return (0);
}

int	expr_unary_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int			efail;
	t_exprdata	*data;

	(void)op;
	if ((!ast->left || !ast->left->name) && (!ast->right || !ast->right->name))
		return (EXPR_BADEXPR);
	else if (ast->left && ast->left->name && ast->right && ast->right->name)
		return (EXPR_OPMISS);
	if (!(ast = (ast->u == 1 ? ast->right : ast->left)))
		return (EXPR_BADEXPR);
	if ((efail = ft_astiter(ast, res, iterf)))
		return (efail);
	if (*ast->parent->name == '-')
		*(EXPRT *)res = -(*(EXPRT *)res);
	else if (*ast->parent->name == '!')
		*(EXPRT *)res = !(*(EXPRT *)res);
	else if (*ast->parent->name == '~')
		*(EXPRT *)res = ~(*(EXPRT *)res);
	else if (*ast->parent->name == '@' && (efail = *(int *)res))
	{
		data = (t_exprdata *)ast->data;
		if ((*(EXPRT *)res = 0) || efail < data->args->argc)
			*(EXPRT *)res = ft_atoi(data->args->argv[efail]);
	}
	return (0);
}

int	expr_tern_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	(void)iterf;
	if (*ast->name == ',')
	{
		if (!ft_astgood(ast))
			return (EXPR_EXPECT);
		*(EXPRT *)res = *(EXPRT *)op[1];
		return (0);
	}
	if (*ast->name == ':')
		return (EXPR_BADEXPR);
	if (!ast->right || !ast->right->name || *ast->right->name != ':')
		return (EXPR_EXPECT);
	if (!ast->right->left || !ast->right->left->name
			|| !ast->right->right || !ast->right->right->name)
		return (EXPR_OPMISS);
	if (*(EXPRT *)op[0])
		return (ft_astiter(ast->right->left, res, iterf));
	return (ft_astiter(ast->right->right, res, iterf));
}
