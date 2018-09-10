/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:37:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/06 19:03:20 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static int	strexpand1(t_list *it, t_expf *expf, char **res)
{
	t_strid	*s;
	char	*cur;
	int		efail;

	while (it && (s = (t_strid *)it->content))
	{
		cur = NULL;
		s->next = *res;
		if (!(s->jump = 0) && s->ifound == -1)
			*res = ft_strn2join_clr(s->str, *res, s->len, 1);
		else if (expf->expansions[s->ifound].func)
		{
			if ((efail = expf->expansions[s->ifound].func(s, &cur, expf)))
				return (ft_memdel_x(2, res, &cur) ? efail : efail);
			if (cur == s->str)
				cur = ft_strn2join(cur, *res + s->jump, s->len);
			else
				cur = ft_strjoin_clr(cur, *res + s->jump, 0);
			*ft_memdel((void **)res) = cur;
		}
		else
			*res = ft_strn2join_clr(s->str, *res, s->len, 1);
		it = it->next;
	}
	return (0);
}

int			ft_strexpand(const char *origin, char **res, int i, t_expf *expf)
{
	t_list	*head;
	t_strid	strid;
	int		pos;
	int		efail;

	head = NULL;
	strid.i = i;
	strid.j = 0;
	strid.next = NULL;
	while (*origin)
	{
		pos = ft_strpbrkstrp_pos(origin, 0, expf->len, expf->expansions,
				sizeof(t_exp), 0);
		strid.ifound = (pos == 0 ? g_ifound : -1);
		if ((strid.str = (char *)origin) && pos == 0)
			strid.len = g_iread;
		else
			strid.len = (pos == -1 ? (int)ft_strlen(origin) : pos);
		origin += strid.len;
		ft_lstpushfront(&head, ft_lstnew(&strid, sizeof(t_strid)));
		++strid.j;
	}
	efail = strexpand1(head, expf, res);
	ft_lstdel(&head, content_delfunc);
	return (efail);
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
