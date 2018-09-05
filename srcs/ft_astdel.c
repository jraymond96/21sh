/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 01:54:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:22:37 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_list.h"
#include "ft_printf.h"
#include "ft_types.h"

void		ft_astprint(t_ast *bt, int n)
{
	int			i;

	if (!bt)
	{
		ft_printf("%?*\tEND\n", n);
		return ;
	}
	ft_printf("%?*\t'%d': '%s'('%s') unary %d\n", n, bt->type, bt->name,
			(bt->parent ? bt->parent->name : NULL), bt->u);
	if (bt->type == bt->cmd_offset && bt->args && bt->args->argc > 1)
	{
		i = -1;
		ft_printf("%?*\tArgs: \n", n + 1);
		while (++i < bt->args->argc)
			ft_printf("%?*\t '%s'\n", n + 1, bt->args->argv[i]);
	}
	ft_printf("%?*\tLeft {\n", n);
	ft_astprint(bt->left, n + 1);
	ft_printf("%?*\t}\n%1$?*\tRight {\n", n);
	ft_astprint(bt->right, n + 1);
	ft_printf("%?*\t}\n", n);
}

int			ft_astvalid(t_ast *ast)
{
	if (!ast || !ast->name)
		return (0);
	return (1);
}

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

	left = NULL;
	right = NULL;
	if (ast && *ast)
	{
		left = (*ast)->left;
		right = (*ast)->right;
		astdelone(ast);
		ft_astdel(&left);
		ft_astdel(&right);
	}
}
