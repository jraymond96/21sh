/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:48:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/17 16:28:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_insert(t_btree *bt, t_btree *elem)
{
	return (ft_btree_insertf(bt, elem, ft_memcmp));
}

t_btree	*ft_btree_insertf(t_btree *bt,
						t_btree *elem,
						t_cmpfunc cmp)
{
	if (bt == NULL || bt == elem)
		return (elem);
	if (cmp(bt->content, elem->content, elem->content_size) > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = elem))
				elem->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = elem))
				elem->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_insertf(bt, elem, cmp));
}

t_btree	*ft_btree_insertm(t_btree *bt,
						t_btree *elem,
						size_t pstart,
						size_t plen)
{
	if (bt == NULL || bt == elem)
		return (elem);
	if (ft_memcmp((char *)bt->content + pstart,
				(char *)elem->content + plen, plen) > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = elem))
				elem->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = elem))
				elem->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_insertm(bt, elem, pstart, plen));
}
