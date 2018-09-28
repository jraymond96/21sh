/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_getnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:13:10 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:13:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree		*ft_btree_getnewf(t_btree *bt,
						void *content,
						size_t content_size,
						t_cmpfunc cmp)
{
	int		cmp_n;

	if (!bt)
		return (ft_btree_new(content, content_size));
	if ((cmp_n = cmp(bt->content, content, content_size)) == 0)
		return (bt);
	else if (cmp_n > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = ft_btree_new(content, content_size)))
				bt->left->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = ft_btree_new(content, content_size)))
				bt->right->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_getnewf(bt, content, content_size, cmp));
}

t_btree		*ft_btree_getnewm(t_btree *bt,
						void *content,
						size_t content_size,
						t_ptrpos ptrpos)
{
	int		cmp_n;

	if (!bt)
		return (ft_btree_new(content, content_size));
	if ((cmp_n = ft_memcmp(bt->content + ptrpos.start,
					content + ptrpos.start, ptrpos.len)) == 0)
		return (bt);
	else if (cmp_n > 0)
	{
		if (bt->left == NULL)
			if ((bt->left = ft_btree_new(content, content_size)))
				bt->left->parent = bt;
		bt = bt->left;
	}
	else
	{
		if (bt->right == NULL)
			if ((bt->right = ft_btree_new(content, content_size)))
				bt->right->parent = bt;
		bt = bt->right;
	}
	return (ft_btree_getnewm(bt, content, content_size, ptrpos));
}

t_btree		*ft_btree_getnew(t_btree *bt, void *content, size_t content_size)
{
	return (ft_btree_getnewf(bt, content, content_size, ft_memcmp));
}

t_ptrpos	make_ptrpos(size_t pstart, size_t plen)
{
	t_ptrpos ptrpos;

	ptrpos.start = pstart;
	ptrpos.len = plen;
	return (ptrpos);
}
