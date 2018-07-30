/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:37:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/25 17:17:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

static int	strexpand2(const char **origin, char **res, t_expf *expf, int n[4])
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

static int	strexpand1(const char *origin, char **res, int i, t_expf *expf)
{
	int		n[4];

	if (!origin || !res || !expf)
		return (-1);
	*res = NULL;
	ft_bzero(n, sizeof(int) * 4);
	n[2] = i;
	while (*origin && (!n[1] || !expf->onlyfirst))
	{
		n[3] = ft_strpbrkstrp_pos(origin, 0, expf->len,
				(void *)expf->expansions, sizeof(t_exp), 0);
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

	ast->name = NULL;
	if (!ast || !ast->args || !ast->args->argv)
		return (0);
	if ((efail = ft_resolver(ast->args, expf)))
		return (efail);
	ast->name = ast->args->argv[0];
	return (0);
}

int			ft_astcresolver(t_ast *ast, t_expf *expf)
{
	int	efail;

	ft_argsdel(ast->cargs);
	ft_memdel((void **)&ast->cargs);
	ast->cargs = NULL;
	ast->cname = NULL;
	if (!ast || !ast->args || !ast->args->argv
			|| !(ast->cargs = ft_argscopy(ast->args)))
		return (0);
	if ((efail = ft_resolver(ast->cargs, expf)))
		return (efail);
	ast->cname = ast->cargs->argv[0];
	return (0);
}
