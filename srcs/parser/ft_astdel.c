/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 01:54:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/19 20:06:05 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_list.h"
#include "ft_printf.h"
#include "ft_types.h"

void		astdelone(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->type >= (*ast)->op_offset || !(*ast)->args)
		ft_memdel((void **)&(*ast)->name);
	else if ((*ast)->type == (*ast)->cmd_offset)
	{
		ft_argsdel((*ast)->args);
		ft_argsdel((*ast)->cargs);
		ft_memdel((void **)&(*ast)->args);
		ft_memdel((void **)&(*ast)->cargs);
	}
	ft_memdel((void **)ast);
}

t_ast		*astlink(t_ast *a, t_ast *b, int lr)
{
	if (!a || !b)
		return (a);
	if (lr == 1)
		a->right = b;
	else if (lr == -1)
		a->left = b;
	b->parent = a;
	return (a);
}

void		ft_astdel(t_ast **ast)
{
	t_ast	*left;
	t_ast	*right;

	if (ast && *ast)
	{
		left = (*ast)->left;
		right = (*ast)->right;
		astdelone(ast);
		ft_astdel(&left);
		ft_astdel(&right);
	}
}
