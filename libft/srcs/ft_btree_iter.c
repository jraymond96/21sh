/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:54:21 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 22:17:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

static void	inner_btree_lo(t_btree *bt, void (*f)(t_btree *), int n, int m)
{
	if (!bt)
		return ;
	if (n == m)
		return (f(bt));
	inner_btree_lo(bt->left, f, n + 1, m);
	inner_btree_lo(bt->right, f, n + 1, m);
}

static void	ft_btree_levelorder(t_btree *bt, void (*f)(t_btree *))
{
	int	n;
	int	i;

	n = ft_btree_depth(bt);
	i = 0;
	while (i < n)
		inner_btree_lo(bt, f, 0, i++);
}

void		ft_btree_iterm(t_btree *bt, void (*f)(t_btree *), t_btmode mode)
{
	if (!bt || !f)
		return ;
	if (mode == BT_LEVELORDER)
		return (ft_btree_levelorder(bt, f));
	if (mode == BT_PREORDER)
		f(bt);
	ft_btree_iterm(bt->left, f, mode);
	if (mode == BT_INORDER)
		f(bt);
	ft_btree_iterm(bt->right, f, mode);
	if (mode == BT_POSTORDER)
		f(bt);
}

void		ft_btree_iter(t_btree *bt, void (*f)(t_btree *))
{
	ft_btree_iterm(bt, f, BT_INORDER);
}
