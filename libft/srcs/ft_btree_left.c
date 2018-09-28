/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:19:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 21:48:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_left(t_btree *bt)
{
	while (bt && bt->left)
		bt = bt->left;
	return (bt);
}

t_btree	*ft_btree_leftrotate(t_btree *bt)
{
	t_btree	*right;
	int		pos;

	right = bt;
	if (bt && (right = bt->right))
	{
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = right;
		else if (pos == 1)
			bt->parent->right = right;
		bt->right = right->left;
		right->parent = bt->parent;
		right->left = bt;
		bt->parent = right;
		if (bt->right)
			bt->right->parent = bt;
	}
	return (right);
}

t_btree	*ft_btree_leftrotatef(t_btree *bt, t_cmpfunc cmp)
{
	t_btree	*right;
	int		pos;

	right = bt;
	if (cmp && bt && (right = bt->right))
	{
		if (cmp(bt->content, right->content, bt->content_size) >= 0)
			return (bt);
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = right;
		else if (pos == 1)
			bt->parent->right = right;
		bt->right = right->left;
		right->parent = bt->parent;
		right->left = bt;
		bt->parent = right;
		if (bt->right)
			bt->right->parent = bt;
	}
	return (right);
}

t_btree	*ft_btree_leftrotatem(t_btree *bt, size_t start, size_t len)
{
	t_btree	*right;
	int		pos;

	right = bt;
	if (bt && (right = bt->right))
	{
		if (ft_memcmp(bt->content + start, right->content + start, len) >= 0)
			return (bt);
		if ((pos = ft_btree_pos(bt->parent, bt)) == -1)
			bt->parent->left = right;
		else if (pos == 1)
			bt->parent->right = right;
		bt->right = right->left;
		right->parent = bt->parent;
		right->left = bt;
		bt->parent = right;
		if (bt->right)
			bt->right->parent = bt;
	}
	return (right);
}
