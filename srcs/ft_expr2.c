/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expr2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:21:43 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/25 20:31:15 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_types.h"
#include "ft_str.h"
#include "ft_printf.h"

int					g_exprerr;
char				*g_exprstr;

static int			op_result(int a, int b, char *op)
{
	if (*op == '+' || *op == '-')
		return (*op == '+' ? a + b : a - b);
	else if (*op == '*')
		return (a * b);
	else if (*op == '%' || *op == '/')
	{
		if (!b && (g_exprerr = EXPR_DIVZERO))
			return (0);
		return (*op == '%' ? a % b : a / b);
	}
	else if (ft_strequ(op, "<=") || ft_strequ(op, ">="))
		return (*op == '<' ? (a <= b) : (a >= b));
	else if (*op == '<' || *op == '>')
		return (*op == '<' ? (a < b) : (a > b));
	else if (ft_strequ(op, "=="))
		return (a == b);
	else if (ft_strequ(op, "&&") || ft_strequ(op, "||"))
		return (*op == '&' ? (a && b) : (a || b));
	else if (*op == '&' || *op == '|')
		return (*op == '&' ? (a & b) : (a | b));
	else if (*op == '^' || *op == '=')
		return (*op == '^' ? a ^ b : b);
	return (0);
}

static int			equal_op(t_ast *ast, t_exprdata *data)
{
	int		res;
	int		lright;
	char	*tmp;

	if (!ft_strmatch_x(ast->left->name, EXPR_DLM_VARV)
			&& (g_exprerr = EXPR_LVALREQ))
		return (0);
	lright = ft_ast_iter(ast->right, data);
	res = ft_atoi(ft_getenv(ast->left->name, data->var_db));
	res = op_result(res, lright, ast->name);
	if (g_exprerr != EXPR_OK)
		return (0);
	ft_setenv(ast->left->name, (tmp = ft_itoa(res)), &data->var_db);
	free(tmp);
	return (res);
}

static int			unary_op(t_ast *ast, t_exprdata *data)
{
	int		res;
	int		lres;
	char	*tmp;
	char	*ltmp;

	if (ft_strequ(ast->name, "++") || ft_strequ(ast->name, "--"))
	{
		tmp = (ast->u == 1 ? ast->right->name : ast->left->name);
		if (!ft_strmatch_x(tmp, EXPR_DLM_VARV))
			return ((g_exprerr = EXPR_LVALREQ) ? 0 : 0);
		res = ft_atoi(ft_getenv(tmp, data->var_db));
		if (*ast->name == '+')
			lres = (ast->u == 1 ? ++res : res++);
		else
			lres = (ast->u == 1 ? --res : res--);
		ft_setenv(tmp, (ltmp = ft_itoa(res)), &data->var_db);
		free(ltmp);
		return (lres);
	}
	else if (*ast->name == '+' || *ast->name == '-')
	{
		res = ft_ast_iter(ast->right, data);
		res = (*ast->name == '+' ? res : -res);
	}
	return (0);
}

int					ft_ast_iter(t_ast *ast, t_exprdata *data)
{
	int		res;
	int		lres;
	int		lright;

	res = 0;
	g_exprerr = 0;
	if (!ast)
		return (0);
	if (ast->type > 0)
	{
		if (!ast->u && (!ast->left || !ast->left->name || !ast->right || !ast->right->name)
				&& (g_exprerr = EXPR_OPMISS))
		{
			g_exprstr = ft_strdup(ast->name);
			return (0);
		}
		if (ast->u)
			return (unary_op(ast, data));
		if (ft_strmatch_x(ast->name, EXPR_DLM_EQU))
			return (equal_op(ast, data));
		else
			lres = ft_ast_iter(ast->left, data);
		if (g_exprerr != EXPR_OK)
			return (0);
		if (ft_strequ(ast->name, "&&") && !lres)
			return (0);
		else if (ft_strequ(ast->name, "||") && lres)
			return (1);
		lright = ft_ast_iter(ast->right, data);
		if (g_exprerr != EXPR_OK)
			return (0);
		res = op_result(lres, lright, ast->name);
		if (g_exprerr != EXPR_OK)
			return (0);
	}
	else
	{
		if (ast->args->argc > 1 && (g_exprerr = EXPR_BADEXPR))
		{
			g_exprstr = ft_strdup(ast->args->argv[1]);
			return (0);
		}
		ft_resolver(ast->args, 1);
		ast->name = ast->args->argv[0];
		res = (ast->name ? ft_atoi(ast->name) : 0);
	}
	return (res);
}

