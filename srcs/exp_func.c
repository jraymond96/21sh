/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:10:47 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/18 19:31:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_printf.h"

int	exp_var(char *tld, int n[3], void *data, char **res)
{
	char	*value;
	char	tmp;

	(void)data;
	tmp = tld[n[0]];
	tld[n[0]] = '\0';
	if ((value = ft_getenv(tld + 1, g_shell->envp)))
		*res = ft_strdup(value);
	tld[n[0]] = tmp;
	return (0);
	ft_printf("var expansion: '%.*s' %d %d\n", n[0], tld, n[1], n[2]);
}

int	exp_arth(char *tld, int n[3], void *data, char **res)
{
	(void)data;
	*res = tld;
	return (0);
	ft_printf("arithmetic expansion '%.*s' %d %d\n", n[0], tld, n[1], n[2]);
}

int	exp_tild(char *tld, int n[3], void *data, char **res)
{
	char	*homestr;

	(void)data;
	if (n[1] <= 0 && (!tld[1] || tld[1] == '/'))
	{
		if ((homestr = ft_getenv("HOME", g_shell->envp)))
			*res = ft_strdup(homestr);
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
	char	*str;
	char	*tmp;
	char	sep;

	(void)data;
	sep = *(tld + (*tld == '$' ? 1 : 0));
	if (!(str = ft_strbetweenl(tld, sep, sep)))
		return (1);
	*res = str;
	if (*tld == '$' && (tmp = ft_strdupk(str)))
	{
		free(str);
		*res = tmp;
	}
	return (0);
	ft_printf("farg expansion '%.*s' %d %d\n", n[0], tld, n[1], n[2]);
}
