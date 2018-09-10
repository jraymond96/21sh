/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_dump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:38 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/25 15:07:15 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_printf.h"

void	inner_btree_dump(t_btree *bt, int n)
{
	if (!bt)
	{
		ft_printf("%?*\tEND\n", n);
		return ;
	}
	ft_printf("%?*\t'%ld': '%s'('%s')\n%1$?*\tLeft {\n", n, bt->content_size,
			(char *)bt->content,
			(char *)(bt->parent ? bt->parent->content : NULL));
	inner_btree_dump(bt->left, n + 1);
	ft_printf("%?*\t}\n%1$?*\tRight {\n", n);
	inner_btree_dump(bt->right, n + 1);
	ft_printf("%?*\t}\n", n);
}

void	ft_btree_dump(t_btree *bt)
{
	inner_btree_dump(bt, 0);
}

void	inner_btree_dumpf(t_btree *bt, void (*f)(t_btree *), int n)
{
	if (!bt)
	{
		ft_printf("%?*\tEND\n", n);
		return ;
	}
	ft_printf("%?*\t", n);
	if (f)
		f(bt);
	ft_printf("\n%1$?*\tLeft {\n", n);
	inner_btree_dumpf(bt->left, f, n + 1);
	ft_printf("%?*\t}\n%1$?*\tRight {\n", n);
	inner_btree_dumpf(bt->right, f, n + 1);
	ft_printf("%?*\t}\n", n);
}

void	ft_btree_dumpf(t_btree *bt, void (*f)(t_btree *))
{
	inner_btree_dumpf(bt, f, 0);
}
