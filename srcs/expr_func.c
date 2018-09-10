/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:12:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/16 23:12:00 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_printf.h"

int	expr_parenthesis(char *tld, int n[3], t_exprdata *data, char **res)
{
	char	tmp;
	EXPRT	value;
	int		efail;

	if ((tmp = tld[n[0] - 1]) != ')')
		return (EXPR_NCLOSEPAR);
	tld[n[0] - 1] = '\0';
	value = 0;
	if ((efail = ft_expr(tld + 1, &value, data, data->vp)))
		return (efail);
	tld[n[0] - 1] = tmp;
	*res = ft_lltoa(value);
	return (0);
}

int	expr_function(char *tld, int n[3], t_exprdata *data, char **res)
{
	int	pos;

	(void)data;
	(void)n;
	pos = ft_strpbrk_pos(tld, "( ");
	if (ft_strnequ(tld, "strlen", pos))
	{
		*res = ft_uitoa(ft_strlen(tld + pos) - 2);
		return (0);
	}
	return (EXPR_UNKFUNC);
}

int	expr_parameter(char *tld, int n[3], t_exprdata *data, char **res)
{
	int		i;
	int		l;
	int		val;
	va_list	vp;

	(void)n;
	i = 0;
	l = ft_atoi(tld + 1);
	va_copy(vp, data->vp);
	while (i++ < l)
		val = va_arg(vp, EXPRT);
	va_end(vp);
	*res = ft_lltoa(val);
	return (0);
}

int	expr_variable(char *tld, int n[3], t_exprdata *data, char **res)
{
	char	*value;
	char	tmp;

	if (!ft_strmatch_x(tld, EXPR_DLM_VARV))
		return (EXPR_BADEXPR);
	tmp = tld[n[0]];
	tld[n[0]] = '\0';
	if (!(value = ft_getenv(tld, *data->var_db)))
	{
		*res = ft_strdup("0");
		return (0);
	}
	tld[n[0]] = tmp;
	*res = ft_strdup(value);
	return (0);
}
