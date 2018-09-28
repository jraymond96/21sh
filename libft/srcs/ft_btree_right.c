/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:20:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 21:48:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_right(t_btree *bt)
{
	while (bt && bt->right)
		bt = bt->right;
	return (bt);
}

t_btree	*ft_btree_rightrotate(t_btree *bt)
{
	t_btree	*left;
	int		pos;

	left = bt;
	if (bt && (left = bt->left))
	{
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = left;
		else if (pos == 1)
			bt->parent->right = left;
		bt->left = left->right;
		left->parent = bt->parent;
		left->right = bt;
		bt->parent = left;
		if (bt->left)
			bt->left->parent = bt;
	}
	return (left);
}

t_btree	*ft_btree_rightrotatef(t_btree *bt, t_cmpfunc cmp)
{
	t_btree	*left;
	int		pos;

	left = bt;
	if (cmp && bt && (left = bt->left))
	{
		if (cmp(bt->content, left->content, bt->content_size) < 0)
			return (bt);
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = left;
		else if (pos == 1)
			bt->parent->right = left;
		bt->left = left->right;
		left->parent = bt->parent;
		left->right = bt;
		bt->parent = left;
		if (bt->left)
			bt->left->parent = bt;
	}
	return (left);
}

t_btree	*ft_btree_rightrotatem(t_btree *bt, size_t start, size_t len)
{
	t_btree	*left;
	int		pos;

	left = bt;
	if (bt && (left = bt->left))
	{
		if (ft_memcmp(bt->content + start, left->content + start, len) < 0)
			return (bt);
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = left;
		else if (pos == 1)
			bt->parent->right = left;
		bt->left = left->right;
		left->parent = bt->parent;
		left->right = bt;
		bt->parent = left;
		if (bt->left)
			bt->left->parent = bt;
	}
	return (left);
}
