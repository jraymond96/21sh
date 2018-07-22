/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 20:49:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/18 20:14:18 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_math.h"
#include "ft_printf.h"

static t_exp		g_exps[] = {
	{"*[(*);\"?\";'?'@b]:(*[@>0]", NULL, 0},
	{"\"*\":'*':\"*:'*", NULL, 0},
};

static t_op			g_ops[] = {
	{"++:--", OP_UNARYLR},
	{"!:~:+:-:@", OP_UNARYL},
	{"*[*@=2]", OP_BINARY},
	{"*[*%/@=1]", OP_BINARY},
	{"+:-", OP_BINARY},
	{"<<:>>:&:^:|", OP_BINARY},
	{"<:>:<=:>=:!=:==", OP_BINARY},
	{"&&:||", OP_BINARY},
	{"\\:", OP_BINARY},
	{"<<=:>>=:*[+\\-*%/&|^@=1]=:=", OP_ASSOCRL | OP_BINARY},
	{"?", OP_BINARY},
	{",", OP_BINARY},
};

static t_lexerf		g_arithmetic_lexer = {
	{
		" :\t",
		"", "", "",
		",:<<:>>:<<=:>>=:++:--:*[*@=2]:&&:||:>=:<=:==:!=:"
		"*[+\\-*/%&|^@=1]=:*[+\\-*%/<>=&|^!~?\\:@=1]:@",
		g_exps, sizeof(g_exps) / sizeof(t_exp), NULL, NULL, NULL
	}, g_ops, sizeof(g_ops) / sizeof(t_op), 0, 1, NULL
};

static int			expr_par_cb(t_ast *ast, void **op, void *res,
							t_iterf *iterf)
{
	int			efail;
	char		*ptr;
	t_exprdata	*data;

	(void)iterf;
	(void)op;
	if (ast->args && ast->args->argc > 1)
		return (EXPR_OPTMISS);
	data = (t_exprdata *)ast->data;
	if (*(ptr = ft_strend(ast->name)) != ')')
		return (EXPR_PAREXPECT);
	*ptr = '\0';
	efail = ft_vexpr(ast->name + 1, (EXPRT *)res, data, data->vp);
	*ptr = ')';
	return (efail);
}

static int			expr_cmd_cb(t_ast *ast, void **op, void *res,
							t_iterf *iterf)
{
	char		*ptr;
	t_exprdata	*data;

	(void)iterf;
	(void)op;
	if (ast->args && ast->args->argc > 1)
		return (EXPR_OPTMISS);
	data = (t_exprdata *)ast->data;
	if (ft_isdigit(*ast->name))
	{
		if (ft_strmatch(ast->name, "**[aA_-zZ_]*"))
			return (EXPR_BADEXPR);
		*(EXPRT *)res = (EXPRT)ft_atoll(ast->name);
	}
	else if (!(ptr = ft_getenv(ast->name, *data->var_db)))
		*(EXPRT *)res = (EXPRT)0;
	else if (!ft_isdigit(*ptr))
		return (EXPR_NOTINT);
	else
		*(EXPRT *)res = (EXPRT)ft_atoll(ptr);
	return (0);
}

static t_astfunc	g_expr_callbacks[] = {
	{"*[(*);\"?\";'?'@b]:(*", expr_par_cb, NULL, 3},
	{"", expr_cmd_cb, NULL, 3},
	{"++:--", NULL, expr_incdec_cb, 0},
	{"*[*@=2]:*[*%/&|^@=1]:<<:>>", expr_arth_cb, NULL, 2},
	{"+:-", expr_arth_cb, expr_unary_cb, 2},
	{"<:>:<=:>=:==:!=:", expr_comp_cb, NULL, 2},
	{"!:~:@", NULL, expr_unary_cb, 0},
	{"&&:||", expr_cond_cb, NULL, -1},
	{"*[\\-+*%/&|^@=1]=:=:<<=:>>=", expr_equ_cb, NULL, 1},
	{"?:\\:", expr_tern_cb, NULL, -1},
	{",", expr_tern_cb, NULL, 2}
};

static t_iterf		g_arithmetic_iter = {
	g_expr_callbacks, sizeof(g_expr_callbacks) / sizeof(t_astfunc),
	NULL, EXPR_OPMISS, sizeof(EXPRT)
};

int					ft_expr(const char *expr, EXPRT *res,
						t_exprdata *data, ...)
{
	int			efail;
	va_list		vp;

	va_start(vp, data);
	efail = ft_vexpr(expr, res, data, vp);
	va_end(vp);
	return (efail);
}

int					ft_vexpr(const char *expr, EXPRT *res,
						t_exprdata *data, va_list vp)
{
	int			efail;
	t_ast		*ast;
	t_exprdata	edata;

	if (!expr || !res)
		return (EXPR_MEMERR);
	if (!data)
		data = ft_bzero(&edata, sizeof(t_exprdata));
	va_copy(data->vp, vp);
	g_arithmetic_lexer.data = (void *)data;
	ast = ft_lexer(expr, &g_arithmetic_lexer);
	++data->expr_lvl;
	efail = ft_astiter(ast, res, &g_arithmetic_iter);
	--data->expr_lvl;
	va_end(data->vp);
	ft_astdel(&ast);
	return (efail);
}

static t_op			g_exprerrs[] = {
	{"memory error", EXPR_MEMERR},
	{"missing closing parenthesis", EXPR_NCLOSEPAR},
	{"syntax error", EXPR_BADEXPR},
	{"unknown function", EXPR_UNKFUNC},
	{"unknown variable", EXPR_UNKVAR},
	{"division by zero", EXPR_DIVZERO},
	{"lvalue required", EXPR_LVALREQ},
	{"operand missing", EXPR_OPMISS},
	{"expected operator", EXPR_OPTMISS},
	{"expected ')'", EXPR_PAREXPECT},
	{"expected '\"' or '''", EXPR_QUOEXPECT},
	{"arithmetic expression with non-integer value", EXPR_NOTINT},
	{"expecting operator", EXPR_EXPECT},
	{"index out of range", EXPR_OUTRANGE}
};
static size_t		g_exprerrs_len = (sizeof(g_exprerrs) / sizeof(t_op));

char				*ft_exprerr(int efail)
{
	size_t	i;

	i = 0;
	while (i < g_exprerrs_len)
	{
		if (efail == g_exprerrs[i].t)
		{
			return (g_exprerrs[i].name);
		}
		++i;
	}
	return ("error");
}
