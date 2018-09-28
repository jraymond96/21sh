/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 21:09:56 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 23:07:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

static t_btree	*ft_btree_move_case(t_btree *bt, t_btree *elem, int pos)
{
	int		pos0;
	t_btree	*tmp;
	t_btree	*tmp0;

	tmp0 = elem;
	while ((pos0 = ft_btree_pos(tmp0->parent, tmp0)) == pos * -1)
		tmp0 = tmp0->parent;
	ft_btree_disconnect(tmp0);
	if (pos == -1)
	{
		tmp = ft_btree_left(elem);
		if ((tmp->left = tmp0))
			tmp0->parent = tmp;
		tmp = ft_btree_right(elem);
		tmp->right = bt;
	}
	else
	{
		tmp = ft_btree_right(elem);
		if ((tmp->right = tmp0))
			tmp0->parent = tmp;
		tmp = ft_btree_left(elem);
		tmp->left = bt;
	}
	return (tmp);
}

t_btree			*ft_btree_move(t_btree *bt, t_btree *elem)
{
	int		pos;
	t_btree	*tmp;

	if ((pos = ft_btree_pos(bt, elem)) == 0)
		return (bt);
	tmp = ft_btree_move_case(bt, elem, pos);
	ft_btree_disconnect(elem);
	if ((pos = ft_btree_pos(bt, bt->parent)) == -1)
		bt->parent->left = elem;
	else if (pos == 1)
		bt->parent->right = elem;
	bt->parent = tmp;
	return (elem);
}

t_btree			*ft_btree_disconnect(t_btree *bt)
{
	int	pos;

	if (bt && (pos = ft_btree_pos(bt->parent, bt)) != 0)
	{
		if (pos == -1)
			bt->parent->left = NULL;
		else
			bt->parent->right = NULL;
	}
	bt->parent = NULL;
	return (bt);
}

t_btree			*ft_btree_connect(t_btree *a, t_btree *b, int lr)
{
	if (!a || !b || !lr)
		return (NULL);
	if (lr < 0)
		a->left = b;
	else if (lr > 0)
		a->right = b;
	b->parent = a;
	return (a);
}
