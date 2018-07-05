/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:01:38 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/04 02:05:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_list.h"
#include "ft_printf.h"
#include "ft_types.h"

char		*typestr(int type)
{
	static char	*strfree;

	if (strfree)
		ft_memdel((void **)&strfree);
	if (type == TK_CMD)
		return ("TK_CMD");
	else if (type == TK_OP)
		return ("TK_OP");
	else if (type == TK_LEFT)
		return ("TK_LEFT");
	else if (type == TK_LLEFT)
		return ("TK_LLEFT");
	else if (type == TK_RIGHT)
		return ("TK_RIGHT");
	else if (type == TK_LRIGHT)
		return ("TK_LRIGHT");
	else if (type == TK_REDIR)
		return ("TK_REDIR");
	else if (type == TK_PIPE)
		return ("TK_PIPE");
	else if (type == TK_ANDOR)
		return ("TK_ANDOR");
	else if (type == TK_SEMICOLON)
		return ("TK_SEMICOLON");
	return ((strfree = ft_itoa(type)));
}

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

void		astdelone(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->type == (*ast)->cmd_offset)
	{
		ft_argsdel((*ast)->args);
		ft_memdel((void **)&(*ast)->args);
	}
	else if ((*ast)->type >= (*ast)->op_offset)
		ft_memdel((void **)&(*ast)->name);
	ft_memdel((void **)ast);
}

t_ast			*astlink(t_ast *a, t_ast *b, int lr)
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
