/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:37:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/11 20:49:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
/*
static int	chunkresolver(char *str[2], int j, int ig, t_args *args)
{
	int		i;
	int		n[3];

	n[1] = j;
	n[2] = ig;
	if ((n[0] = ft_strpbrkstrl_len(str[0], args->exp_all)))
	{
		i = -1;
		while (args->exps && ++i < (int)args->exps_len)
			if (ft_strpbrkstr_len(str[0], args->exps[i].name))
				break ;
		if (i == (int)args->exps_len || !args->exps[i].func)
			str[1] = ft_strndup(str[0], n[0]);
		else if ((i = args->exps[i].func(str[0], n, args->data, &str[1])))
			return (i);
		if (str[1] == str[0])
			str[1] = ft_strndup(str[0], n[0]);
		str[0] += n[0];
		return (0);
	}
	if ((n[0] = ft_strpbrkstrl_pos(str[0], args->exp_all)) == -1)
		n[0] = (int)ft_strlen(str[0]);
	str[1] = ft_strndup(str[0], n[0]);
	str[0] += n[0];
	return (0);
}

int			ft_resolver(t_args *args, int onlyfirst)
{
	int		is[3];
	char	*str[2];
	char	*final;

	if (!args || !args->argv)
		return (0);
	is[0] = -1;
	while (++is[0] < args->argc && ((onlyfirst && is[0] == 0) || !onlyfirst))
	{
		is[1] = -1;
		final = NULL;
		str[0] = args->argv[is[0]];
		while (*str[0] && ((onlyfirst && is[1] <= 0) || !onlyfirst))
		{
			str[1] = NULL;
			if ((is[2] = chunkresolver(str, ++is[1], is[0], args))
					&& ft_memdel_x(2, (void **)&final, (void **)&str[1]))
				return (is[2]);
			final = ft_strjoin_clr(final, str[1], 2);
		}
		if (final)
			free(args->argv[is[0]]);
		args->argv[is[0]] = (final ? final : args->argv[is[0]]);
	}
	return (0);
}
*/
#include "ft_printf.h"
int			strexpand2(const char **origin, char **res, t_expf *expf, int n[4])
{
	int		t;
	char	*cur;

	cur = NULL;
	t = n[0];
	if (n[3] && !(*res = ft_strnjoin_clr(*res, (char *)*origin,
					(n[3] > 0 ? (size_t)n[3] : ft_strlen(*origin)), 0)))
			return (-1);
	else if (n[3])
		*origin += (n[3] == -1 ? ft_strlen(*origin) : (size_t)n[3]);
	else if (!n[3])
	{
		if (!expf->expansions[g_ifound].func)
			cur = (char *)*origin;
		else if ((n[3] = expf->expansions[g_ifound].func((char *)*origin, n,
						expf->data, &cur)))
			return (ft_memdel_x(2, (void **)res, (void **)&cur) ? n[3] : n[3]);
		if (cur == *origin)
			*res = ft_strnjoin_clr(*res, (char *)*origin, n[0], 0);
		else
			*res = ft_strjoin_clr(*res, cur, 2);
		*origin += t;
	}
	return (0);
}

static int	g_ichan;

int			strexpand1(const char *origin, char **res, int i, t_expf *expf)
{
	int		n[4];

	if (!origin || !res || !expf)
		return (-1);
	*res = NULL;
	ft_bzero(n, sizeof(int) * 4);
	n[2] = i;
	while (*origin && (!n[1] || !expf->onlyfirst))
	{
		n[3] = ft_strpbrkstrp_pos(origin, (void *)expf->expansions, expf->len,
			sizeof(t_exp), 0);
		if (n[3] != -1 && expf->expansions[g_ifound].chan != g_ichan)
			n[3] = g_iread;
		n[0] = g_iread;
		if ((n[3] = strexpand2(&origin, res, expf, n)) == -1)
			return (-1);
		else if (n[3])
			return (n[3]);
		++n[1];
	}
	return (0);
}

int			ft_strexpand(const char *origin, char **res, int i, t_expf *expf)
{
	int		err;
	char	*chunck;

	g_ichan = 0;
	while (g_ichan < expf->num_chan)
	{
		chunck = NULL;
		if (!*res)
			*res = (char *)origin;
		if ((err = strexpand1(*res, &chunck, i, expf)))
			return (err);
		if (*res != origin)
			free(*res);
		*res = chunck;
		++g_ichan;
	}
	if (!*res && origin)
		*res = ft_strnew(0);
	return (0);
}

int			ft_resolver(t_args *args, t_expf *expf)
{
	int		i;
	int		err;
	char	*nwarg;

	i = 0;
	while (i < args->argc && (!i || !expf->onlyfirst))
	{
		nwarg = NULL;
		if ((err = ft_strexpand(args->argv[i], &nwarg, i, expf)))
			return (err);
		if (nwarg)
			free(args->argv[i]);
		args->argv[i] = (nwarg ? nwarg : args->argv[i]);
		++i;
	}
	return (0);
}

int			ft_astresolver(t_ast *ast, t_expf *expf)
{
	int	efail;

	if (!ast || !ast->args || !ast->args->argv)
		return (0);
	if ((efail = ft_resolver(ast->args, expf)))
		return (efail);
	ast->name = ast->args->argv[0];
	return (0);
}
