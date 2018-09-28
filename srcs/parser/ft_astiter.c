/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:35:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/20 21:55:36 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static int	is_post(t_ast *ast, void **op, t_astfunc *func, t_iterf *iterf)
{
	int		efail;
	void	*opw;

	if (func->post == -1)
	{
		opw = (func->func ? op[0] : ast->extra_param);
		if (!(efail = ft_astiter(ast->left, opw, iterf)) && func->func)
			efail = func->func(ast, op, ast->extra_param, iterf);
	}
	else
	{
		opw = (func->func ? op[1] : ast->extra_param);
		if (!(efail = ft_astiter(ast->right, opw, iterf)) && func->func)
			efail = func->func(ast, op, ast->extra_param, iterf);
	}
	ft_memdel_x(2, &op[0], &op[1]);
	return (efail);
}

static int	is_unary(t_ast *ast, void **op, t_astfunc *func, t_iterf *iterf)
{
	int	efail;

	if (ast->u || func->post == 0)
	{
		if (func->unary_func)
			efail = func->unary_func(ast, op, ast->extra_param, iterf);
		else
			efail = iterf->opmissing_err;
	}
	else if (!(efail = func->func(ast, op, ast->extra_param, iterf)))
		if (!(efail = ft_astiter(ast->left, ast->extra_param, iterf)))
			efail = ft_astiter(ast->right, ast->extra_param, iterf);
	return (efail);
}

static int	astiter2(t_ast *ast, void *res, t_astfunc *func, t_iterf *iterf)
{
	void	*op[2];
	int		efail;

	ft_bzero(op, sizeof(void *) * 2);
	ast->extra_param = res;
	if (ast->u || func->post == 0 || func->post == -2)
		return (is_unary(ast, op, func, iterf));
	if (iterf->opmissing_err && !ft_astgood(ast))
		return (iterf->opmissing_err);
	if (!ft_memalloc_xp(2, iterf->bsize, op) && ft_memdel_x(2, &op[0], &op[1]))
		return (-1);
	if (func->post == -1 || func->post == 1)
		return (is_post(ast, op, func, iterf));
	if (!(efail = ft_astiter(ast->left, (func->func ? op[0] : res), iterf)))
		if (!(efail = ft_astiter(ast->right, (func->func ? op[1] : res),
					iterf)) && func->func)
			efail = func->func(ast, (void **)op, res, iterf);
	ft_memdel_xp(2, op);
	return (efail);
}

static int	astiter(t_ast *ast, void *res, t_iterf *iterf)
{
	size_t		i;

	i = 0;
	while (i < iterf->funcs_len)
	{
		if (iterf->funcs[i].post == 3
				&& (!iterf->funcs[i].name
					|| !*iterf->funcs[i].name
					|| ft_strmatch_x(ast->name, iterf->funcs[i].name)))
			break ;
		++i;
	}
	if (i == iterf->funcs_len || !iterf->funcs[i].func)
		return (0);
	return (iterf->funcs[i].func(ast, NULL, res, iterf));
}

int			ft_astiter(t_ast *ast, void *res, t_iterf *iterf)
{
	size_t		i;
	t_astfunc	*func;

	if (!ast || !iterf)
		return (!ast ? 0 : -1);
	if (ast->type != ast->cmd_offset)
	{
		i = 0;
		func = NULL;
		while (i < iterf->funcs_len)
		{
			if (iterf->funcs[i].post != 3
					&& ft_strmatch_x(ast->name, iterf->funcs[i].name))
			{
				func = &iterf->funcs[i];
				break ;
			}
			++i;
		}
		if (!func)
			return (0);
		return (astiter2(ast, res, func, iterf));
	}
	return (astiter(ast, res, iterf));
}
