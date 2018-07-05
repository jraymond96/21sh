/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:35:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/03 02:13:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

int	is_post(t_ast *ast, void **op, void *res, t_astfunc *func, t_iterf *iterf)
{
	int	efail;

	if (func->post == -1)
	{
		if (!(efail = ft_astiter(ast->left, op[0], iterf)))
			efail = func->func(ast, op, res, iterf);
	}
	else
	{
		if (!(efail = ft_astiter(ast->right, op[1], iterf)))
			efail = func->func(ast, op, res, iterf);
	}
	ft_memdel_x(2, &op[0], &op[1]);
	return (efail);
}

int	ft_astgood(t_ast *ast)
{
	if (!ast || !ast->left || !ast->left->name || !ast->right
			|| !ast->right->name)
		return (0);
	return (1);
}

int	astiter2(t_ast *ast, void **res, t_astfunc *func, t_iterf *iterf)
{
	void	*op[2];
	int		efail;

	ft_bzero(op, sizeof(void *) * 2);
	if (ast->u || func->post == 0)
	{
		if (func->unary_func)
			efail = func->unary_func(ast, (void **)op, res, iterf);
		else
			efail = iterf->opmissing_err;
		return (efail);
	}
	if (iterf->opmissing_err && !ft_astgood(ast))
		return (iterf->opmissing_err);
	ft_memalloc_xp(2, iterf->bsize, op);
	if (func->post == -1 || func->post == 1)
		return (is_post(ast, op, res, func, iterf));
	if (!(efail = ft_astiter(ast->left, op[0], iterf)))
		if (!(efail = ft_astiter(ast->right, op[1], iterf)))
			efail = func->func(ast, (void **)op, res, iterf);
	ft_memdel_xp(2, op);
	return (efail);
}

int	ft_astiter(t_ast *ast, void *res, t_iterf *iterf)
{
	size_t		i;
	t_astfunc	*func;

	if (!ast || !iterf)
		return (!ast ? 0 : -1);
	if (ast->type != ast->cmd_offset)
	{
		i = 0;
		func = NULL;
		while (i++ < iterf->funcs_len)
			if (ft_strmatch_x(ast->name, iterf->funcs[i - 1].name)
					&& (func = &iterf->funcs[i - 1]))
				break ;
		if (!func)
			return (0);
		return (astiter2(ast, res, func, iterf));
	}
	return (iterf->op_func(ast, NULL, res, iterf));
}
