/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:58:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/21 18:11:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "get_next_line.h"

int	exp_var(char *tld, int n[3], void *data, char **res)
{
	char	*value;
	char	tmp;

	(void)data;
	tmp = tld[n[0]];
	tld[n[0]] = '\0';
	if (!ft_isalpha(*(tld + 1)) && !ft_isdigit(*(tld + 1)))
	{
		if (*(tld + 1) == '?')
			*res = ft_itoa(g_shell->exitcode);
	}
	else if ((value = ft_getenv(tld + 1, g_shell->envp)))
		*res = ft_strdup(value);
	tld[n[0]] = tmp;
	return (0);
	ft_printf("var expansion: '%.*s' %d %d %d\n", n[0], tld, n[0], n[1], n[2]);
}

int	exp_arth(char *tld, int n[3], void *data, char **res)
{
	EXPRT		val;
	int			err;
	t_exprdata	edata;

	(void)data;
	val = (EXPRT)0;
	tld[n[0] - 2] = '\0';
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((err = ft_expr(tld + 3, &val, &edata)))
	{
		tld[n[0] - 2] = ')';
		*res = NULL;
		return (SH_EXPRERR + err);
	}
	tld[n[0] - 2] = ')';
	*res = ft_lltoa(val);
	return (0);
	ft_printf("arithmetic expansion '%s' %d %d\n", tld + 3, n[1], n[2]);
}

int	exp_tild(char *tld, int n[3], void *data, char **res)
{
	char	*str;
	char	*name;
	int		pm;

	(void)data;
	if (tld[1] == '+' && (pm = 2))
		name = "PWD";
	else if (tld[1] == '-' && (pm = 2))
		name = "OLDPWD";
	else if ((pm = 1))
		name = "HOME";
	if (n[1] <= 0 && (!tld[pm] || tld[pm] == '/'))
	{
		if ((str = ft_getenv(name, g_shell->envp)))
			*res = ft_strdup(str);
		return (0);
	}
	*res = tld;
	return (0);
	ft_printf("tilde expansion '%.*s' %d %d\n", n[0], tld, n[1], n[2]);
}

int	exp_cmd(char *tld, int n[3], void *data, char **res)
{
	(void)data;
	*res = tld;
	return (0);
	ft_printf("command expansion '%.*s' %d %d\n", n[0], tld, n[1], n[2]);
}

int	exp_farg(char *tld, int n[3], void *data, char **res)
{
	char	sep;

	
	(void)data;
	if (n[0] == 1)
		return ((*res = NULL) ? 0 : 0);
	if ((sep = tld[n[0] - 1]) == '\'' || sep == '"')
		tld[n[0] - 1] = '\0';
	if (*tld == '$')
		*res = ft_strdupk(tld + 2);
	else if (tld[0] == '\'')
		*res = ft_strdup(tld + 1);
	else
		*res = ft_strdupl(tld + 1);
	tld[n[0] - 1] = sep;
	return (0);
	ft_printf("farg expansion %d '%s' %d %d '%c'\n", n[0], tld, n[1], n[2], tld[n[0] - 1]);
}
