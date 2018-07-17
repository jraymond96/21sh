/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 06:51:04 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/12 19:21:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"

static char	*checkarg(const char **cmd, t_parserf *pdef)
{
	static char	*str;
	char		*tld;
	int			pos;

	tld = NULL;
	if (!cmd)
		return (str = NULL);
	if ((pos = ft_strpbrkstr_len(*cmd, pdef->exp_all)))
	{
		tld = ft_strndup(*cmd, pos);
		*cmd += pos;
	}
	else if ((pos = ft_strpbrkstrl_pos(*cmd, pdef->def_all)) || !pos)
	{
		tld = (pos == -1 ? ft_strdup(*cmd) : ft_strndup(*cmd, pos));
		*cmd += (pos == -1 ? ft_strlen(*cmd) : (size_t)pos);
	}
	str = ft_strjoin_clr(str, tld, 2);
	if ((!**cmd || ft_strpbrkstr_len(*cmd, pdef->def_word)
				|| ft_strpbrkstr_len(*cmd, pdef->def_hstop)) && (tld = str))
		str = NULL;
	return (!str ? tld : NULL);
}

static void	getalls(t_parserf *pdef, t_args *args)
{
	static char	*def_all;
	static char	*exp_all;
	size_t		i;

	if ((!exp_all || pdef->exp_all != exp_all) && ft_memdel((void **)&exp_all))
	{
		i = 0;
		while (pdef->exps && i < pdef->exps_len)
		{
			if (exp_all)
				exp_all = ft_strjoinc_clr(exp_all, ':');
			exp_all = ft_strjoin_clr(exp_all, pdef->exps[i++].name, 0);
		}
		pdef->exp_all = exp_all;
	}
	if ((!def_all || pdef->def_all != def_all) && ft_memdel((void **)&def_all))
	{
		if (pdef->def_word || pdef->def_hstop || pdef->exp_all)
			ft_printf_s(&def_all, "%js:%js:%js", pdef->def_word,
				pdef->def_hstop, pdef->exp_all);
		pdef->def_all = def_all;
	}
	args->exps = pdef->exps;
	args->exps_len = pdef->exps_len;
	args->exp_all = pdef->exp_all;
}

char		*ft_parser(const char *str, t_args *args, t_parserf *pdef)
{
	char	*s;
	int		pos;

	if (!str || !*str || !args || !pdef)
		return (0);
	while (*str && (pos = ft_strpbrkstr_len(str, pdef->def_word)))
		str += pos;
	if (!*str)
		return (0);
	getalls(pdef, args);
	while (*str && !(pos = ft_strpbrkstr_len(str, pdef->def_hstop)))
	{
		if ((pos = ft_strpbrkstr_len(str, pdef->def_stop)) && (!str[pos]
					|| ft_strpbrkstr_len(str + pos, pdef->def_word)
					|| ft_strpbrkstr_len(str + pos, pdef->def_hstop)))
			break ;
		if ((s = checkarg(&str, pdef)))
			args->argv = ft_memjoin_clr(args->argv,
					sizeof(char *) * args->argc++, &s, sizeof(char *));
		while (*str && (pos = ft_strpbrkstr_len(str, pdef->def_word)))
			str += pos;
	}
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc,
		ft_bzero(&s, sizeof(char *)), sizeof(char *));
	return ((args->data = pdef->data) ? (char *)str : (char *)str);
}

void		ft_argsdel(t_args *args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	if (args->argv)
		while (i < args->argc)
			ft_memdel((void **)&args->argv[i++]);
	ft_memdel((void **)&args->argv);
	ft_bzero(args, sizeof(t_args));
}
