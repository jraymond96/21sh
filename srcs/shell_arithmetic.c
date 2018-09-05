/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_arithmetic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:17:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 22:19:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

int	shell_arth_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	char		*ep;
	char		*epe;
	int			efail;
	t_exprdata	edata;
	EXPRT		val;

	(void)op;
	(void)iterf;
	ep = ast->name + 2;
	epe = ft_strend(ep);
	*epe = '\0';
	val = (EXPRT)0;
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((efail = ft_expr(ep, &val, &edata, g_shell->curargs)))
	{
		*epe = ']';
		return (SH_EXPRERR + efail);
	}
	*epe = ']';
	if (!val)
		*(int *)res = 1;
	else
		*(int *)res = 0;
	return (0);
}

int	exp_arth(t_strid *sid, char **res, t_expf *expf)
{
	EXPRT		val;
	int			err;
	t_exprdata	edata;

	(void)expf;
	val = (EXPRT)0;
	sid->str[sid->len - 2] = '\0';
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((err = ft_expr(sid->str + 3, &val, &edata, g_shell->curargs)))
	{
		sid->str[sid->len - 2] = ')';
		*res = NULL;
		return (SH_EXPRERR + err);
	}
	sid->str[sid->len - 2] = ')';
	*res = ft_lltoa(val);
	return (0);
}

int	exp_cond(t_strid *sid, char **res, t_expf *expf)
{
	EXPRT		val;
	int			err;
	t_exprdata	edata;

	(void)expf;
	val = (EXPRT)0;
	sid->str[sid->len - 1] = '\0';
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((err = ft_expr(sid->str + 2, &val, &edata, g_shell->curargs)))
	{
		sid->str[sid->len - 1] = ']';
		*res = NULL;
		return (SH_EXPRERR + err);
	}
	sid->str[sid->len - 1] = ']';
	*res = ft_lltoa(val);
	return (0);
}
