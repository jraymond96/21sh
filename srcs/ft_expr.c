/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 20:49:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/04 03:44:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_math.h"
#include "ft_printf.h"

int					g_exprerr;

static t_exp		g_exps[] = {
	//{"*[(*)@b]", (t_expfunc)expr_parenthesis},
	//{"(*[\1*-(\177]", (t_expfunc)expr_parenthesis},
	//{"*[aA0_-zZ9_]*[(*)@b]", (t_expfunc)expr_function},
	//{"*[aA0_-zZ9_]*[ ]*[(*)@b]", (t_expfunc)expr_function},
	{EXPR_DLM_VAR, (t_expfunc)expr_variable},
	{"@*[0-9]", (t_expfunc)expr_parameter},
};

static t_op			g_ops[] = {
	{"*[(*)@b]", OP_UNARYLR},
	{"++:--", OP_UNARYLR},
	{"!:~:+:-", OP_UNARYL},
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
	{"return", OP_UNARYL},
	{"if", OP_UNARYL},
	{"then", OP_BINARY},
	{"else", OP_BINARY}
};

static t_lexerf		g_arithmetic_lexer = {
	{
		" :\t",
		"if:else:then:return",
		"*[(*)@b]:,:<<:>>:<<=:>>=:++:--:*[*@=2]:&&:||:>=:<=:==:!="
		"*[+\\-*/%&|^@=1]=:*[+\\-*%/<>=&|^!~?\\:@=1]",
		g_exps, sizeof(g_exps) / sizeof(t_exp), NULL, NULL, NULL
	}, g_ops, sizeof(g_ops) / sizeof(t_op), 0, 1, NULL
};

static int	expr_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int	efail;

	(void)iterf;
	(void)op;
	if (ast->args && ast->args->argc > 1)
		return (EXPR_OPTMISS);
	if ((efail = ft_astresolver(ast, iterf->resolve_first)))
		return (efail);
	if (*ast->name != '-' && *ast->name != '+' && !ft_isdigit(*ast->name))
		return (EXPR_NOTINT);
	*(EXPRT *)res = ft_atoll(ast->name);
	return (0);
}

static t_astfunc	g_expr_callbacks[] = {
		{"++:--", NULL, expr_incdec_cb, 0},
		{"*[*@=2]:*[*%/@=1]:<<:>>", expr_arth_cb, NULL, 2},
		{"+:-", expr_arth_cb, expr_unary_cb, 2},
		{"<:>:<=:>=:==:!=:", expr_comp_cb, NULL, 2},
		{"!:~", NULL, expr_unary_cb, 0},
		{"&&:||", expr_cond_cb, NULL, -1},
		{"&:|:^", expr_arth_cb, NULL, 2},
		{"*[\\-+*%/&|^@=1]=:=:<<=:>>=", expr_equ_cb, NULL, 1},
		{"?:\\:", expr_tern_cb, NULL, -1},
		{",", expr_tern_cb, NULL, 2}
};

static t_iterf		g_arithmetic_iter = {
	expr_cmd_cb, g_expr_callbacks,
	sizeof(g_expr_callbacks) / sizeof(t_astfunc), 1, EXPR_OPMISS, sizeof(EXPRT)
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
	ft_astprint(ast, 0);
	++data->expr_lvl;
	efail = ft_astiter(ast, res, &g_arithmetic_iter);
	--data->expr_lvl;
	va_end(data->vp);
	ft_astdel(&ast);
	return (efail);
}

char				*ft_exprerr(int efail)
{
	if (efail == EXPR_MEMERR)
		return ("memory error");
	else if (efail == EXPR_NCLOSEPAR)
		return ("missing closing parenthesis");
	else if (efail == EXPR_BADEXPR)
		return ("syntax error");
	else if (efail == EXPR_UNKFUNC)
		return ("unknown function");
	else if (efail == EXPR_UNKVAR)
		return ("unknown variable");
	else if (efail == EXPR_DIVZERO)
		return ("forbidden division by zero");
	else if (efail == EXPR_LVALREQ)
		return ("lvalue required");
	else if (efail == EXPR_OPMISS)
		return ("operand missing");
	else if (efail == EXPR_OPTMISS)
		return ("expected operator");
	else if (efail == EXPR_NOTINT)
		return ("arithmetic expression with non-integer value");
	else if (efail == EXPR_EXPECT)
		return ("additionnal operator expected");
	return ("");
}
