/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_getcreate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:54:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:54:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_getcreatef(t_btree *bt,
						void *content,
						size_t content_size,
						t_cmpfunc cmp)
{
	int		cmp_n;

	if (!bt)
		return (ft_btree_create(content, content_size));
	if ((cmp_n = cmp(bt->content, content, content_size)) == 0)
		return (bt);
	else if (cmp_n > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = ft_btree_create(content, content_size)))
				bt->left->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = ft_btree_create(content, content_size)))
				bt->right->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_getcreatef(bt, content, content_size, cmp));
}

t_btree	*ft_btree_getcreatem(t_btree *bt,
						void *content,
						size_t content_size,
						t_ptrpos ptrpos)
{
	int		cmp_n;

	if (!bt)
		return (ft_btree_create(content, content_size));
	if ((cmp_n = ft_memcmp(bt->content + ptrpos.start,
					content + ptrpos.start, ptrpos.len)) == 0)
		return (bt);
	else if (cmp_n > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = ft_btree_create(content, content_size)))
				bt->left->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = ft_btree_create(content, content_size)))
				bt->right->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_getcreatem(bt, content, content_size, ptrpos));
}

t_btree	*ft_btree_getcreate(t_btree *bt, void *content, size_t content_size)
{
	return (ft_btree_getcreatef(bt, content, content_size, ft_memcmp));
}
