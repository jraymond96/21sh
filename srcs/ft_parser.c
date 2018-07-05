/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 06:51:04 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/03 06:51:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static char	*checkarg(const char **cmd, t_parserf *pdef)
{
	static char	*str;
	char		*tld;
	int			pos;

	tld = NULL;
	if (!cmd)
		return (str = NULL);
	if ((pos = ft_strpbrkstr_len(*cmd, pdef->_exp_all)))
	{
		tld = ft_strndup(*cmd, pos);
		*cmd += pos;
	}
	else if ((pos = ft_strpbrkstrl_pos(*cmd, pdef->_def_all)) || !pos)
	{
		tld = (pos == -1 ? ft_strdupl(*cmd) : ft_strndupl(*cmd, pos));
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

	if (!exp_all || pdef->_exp_all != exp_all)
	{
		free(exp_all);
		exp_all = NULL;
		i = 0;
		while (pdef->exps && i < pdef->exps_len)
		{
			if (exp_all)
				exp_all = ft_strjoinc_clr(exp_all, ':');
			exp_all = ft_strjoin_clr(exp_all, pdef->exps[i++].name, 0);
		}
		pdef->_exp_all = exp_all;
	}
	if (!def_all || pdef->_def_all != def_all)
	{
		free(def_all);
		def_all = NULL;
		ft_printf_s(&def_all, "%js:%js:%js", pdef->def_word, pdef->def_hstop,
				pdef->_exp_all);
		pdef->_def_all = def_all;
	}
	args->exps = pdef->exps;
	args->exps_len = pdef->exps_len;
	args->exp_all = pdef->_exp_all;
}

char		*ft_parser(const char *str, t_args *args, t_parserf *pdef)
{
	char	*ustr;
	int		pos;

	if (!str || !args || !*str)
		return (NULL);
	while (*str && (pos = ft_strpbrkstr_len(str, pdef->def_word)))
		str += pos;
	if (!*str)
		return (NULL);
	getalls(pdef, args);
	while (*str && !ft_strpbrkstr_len(str, pdef->def_hstop))
	{
		if ((pos = ft_strpbrkstr_len(str, pdef->def_stop)))
			if (!str[pos] || ft_strpbrkstr_len(str + pos, pdef->def_word))
				break ;
		if ((ustr = checkarg(&str, pdef)))
			args->argv = ft_memjoin_clr(args->argv,
					sizeof(char *) * args->argc++, &ustr, sizeof(char *));
		while (*str && (pos = ft_strpbrkstr_len(str, pdef->def_word)))
			str += pos;
	}
	ustr = NULL;
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc,
		&ustr, sizeof(char *));
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
			free(args->argv[i++]);
	free(args->argv);
	ft_bzero(args, sizeof(t_args));
}
