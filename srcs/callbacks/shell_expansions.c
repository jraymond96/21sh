/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 18:58:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/16 21:14:20 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <sys/wait.h>

int			exp_var(t_strid *sid, char **res, t_expf *expf)
{
	char	*value;
	char	tmp;

	(void)expf;
	if (*sid->str == '\\')
	{
		*res = ft_strndup(sid->str + 1, 1);
		return (0);
	}
	tmp = sid->str[sid->len];
	sid->str[sid->len] = '\0';
	if (!ft_isalpha(*(sid->str + 1)) && !ft_isdigit(*(sid->str + 1)))
	{
		if (*(sid->str + 1) == '?')
			*res = ft_itoa(g_shell->exitcode);
	}
	else if ((value = ft_getenv(sid->str + 1, g_shell->envp)))
		*res = ft_strdup(value);
	sid->str[sid->len] = tmp;
	return (0);
}

int			exp_tild(t_strid *sid, char **res, t_expf *expf)
{
	char	*name;

	(void)expf;
	name = NULL;
	if (!sid->next || *sid->next == '/')
		name = "HOME";
	else if (sid->next && (*sid->next == '+' || *sid->next == '-'))
	{
		if (!sid->next[1] || sid->next[1] == '/')
		{
			sid->jump = 1;
			name = (*sid->next == '+' ? "PWD" : "OLDPWD");
		}
	}
	if (name && sid->j == 0)
		*res = ft_strdup(ft_getenv(name, g_shell->envp));
	else
		*res = sid->str;
	return (0);
}

static t_exp	g_exps[] = {
	{"\\\\*[$`\"@=1]", exp_var},
	{"$*[aA0_-zZ9_]:$?", exp_var},
	{"$*[0-9]:$#", exp_arg},
	{"*[$((?));(?);\"*\";'*'@b]", exp_arth},
	{"*[${?};\"*\";'*'@b]", exp_dvar},
	{"*[`?`;${?};\"*\";'*'@b]", exp_cmd},
	{"*[$\\[*\\];\"*\";'*'@b]", exp_cond}
};

static t_expf	g_expf = {
	g_exps, sizeof(g_exps), NULL, 0
};

int			exp_quote(t_strid *sid, char **res, t_expf *expf)
{
	char	sep;

	g_expf.data = expf->data;
	if (sid->len == 1)
		return ((*res = NULL) ? 0 : 0);
	if ((sep = sid->str[sid->len - 1]) == '\'' || sep == '"')
		sid->str[sid->len - 1] = '\0';
	if (*sid->str == '$')
		*res = ft_strdupk(sid->str + 2);
	else if (*sid->str == '\'')
		*res = ft_strdup(sid->str + 1);
	else
		ft_strexpand(sid->str + 1, res, 0, &g_expf);
	sid->str[sid->len - 1] = sep;
	return (0);
}

int			exp_arg(t_strid *sid, char **res, t_expf *expf)
{
	int	n;

	(void)expf;
	*res = NULL;
	if (g_shell->curargs)
	{
		if (sid->str[1] == '#')
			*res = ft_itoa(g_shell->curargs->argc);
		else if ((n = ft_atoi(sid->str + 1)) < g_shell->curargs->argc)
			*res = ft_strdup(g_shell->curargs->argv[n]);
	}
	return (0);
}
