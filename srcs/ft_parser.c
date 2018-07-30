/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 06:51:04 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/21 21:19:43 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"

static int	checkpos(const char **cmd, t_parserf *pdef)
{
	int	pos;
	int	len;

	if ((pos = ft_strpbrkstrl_pos(*cmd, pdef->def_all)) == -1)
		return (-1);
	len = 0;
	if ((len = ft_strpbrkstr_len(*cmd + pos, pdef->def_word)))
		return (pos);
	if ((len = ft_strpbrkstr_len(*cmd + pos, pdef->def_lstop))
			&& *(*cmd + pos + len)
			&& !ft_strpbrkstr_len(*cmd + pos + len, pdef->def_word)
			&& !ft_strpbrkstr_len(*cmd + pos + len, pdef->def_lstop)
			&& !ft_strpbrkstr_len(*cmd + pos + len, pdef->def_hstop))
	{
		len = ft_strpbrkstr_len(*cmd + pos, pdef->def_hstop);
		return (pos);
	}
	return (pos);
}

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
	else if ((pos = checkpos(cmd, pdef)) != -2)
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

static void	getalls(t_parserf *pdef)
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
			ft_printf_s(&def_all, "%js:%js:%js:%js", pdef->def_word,
				pdef->def_hstop, pdef->def_lstop, pdef->exp_all);
		pdef->def_all = def_all;
	}
}

static int	checkbreak(const char **str, t_parserf *pdef, int *pos)
{
	if ((*pos = ft_strpbrkstrp_len(*str, 1, 2, pdef->def_stop, pdef->def_lstop))
			&& (!(*str)[*pos] || ft_strpbrkstr_len(*str + *pos, pdef->def_word)
				|| ft_strpbrkstr_len(*str + *pos, pdef->def_hstop)))
		return (1);
	if ((*pos = ft_strpbrkstr_len(*str, pdef->def_rstop))
			|| (*pos = ft_strpbrkstr_len(*str, pdef->def_hstop)))
		return (1);
	return (0);
}

int			ft_parser(const char **str, t_args *args, t_parserf *pdef)
{
	char	*s;
	int		pos;

	if (!str || !*str || !**str || !args || !pdef)
		return (-1);
	while (**str && (pos = ft_strpbrkstr_len(*str, pdef->def_word)))
		*str += pos;
	if (!**str)
		return (-1);
	getalls((args->parserf = pdef));
	while (**str)
	{
		if (checkbreak(str, pdef, &pos))
			break ;
		if ((s = checkarg(str, pdef)))
			args->argv = ft_memjoin_clr(args->argv,
					sizeof(char *) * args->argc++, &s, sizeof(char *));
		while (**str && (pos = ft_strpbrkstr_len(*str, pdef->def_word)))
			*str += pos;
	}
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc,
		ft_bzero(&s, sizeof(char *)), sizeof(char *));
	return ((args->data = pdef->data) ? pos : pos);
}
