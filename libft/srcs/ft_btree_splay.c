/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_splay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:16:30 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/22 21:35:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_splay(t_btree *bt, const void *content, size_t content_size)
{
	return (ft_btree_splayf(bt, content, content_size, ft_memcmp));
}

t_btree	*ft_btree_splayf(t_btree *bt,
					const void *content,
					size_t content_size,
					t_cmpfunc cmp)
{
	t_btree	*found;

	if (!(found = ft_btree_searchf(bt, content, content_size, cmp)))
		return (NULL);
	return (ft_btree_move(bt, found));
}

t_btree	*ft_btree_splaym(t_btree *bt,
					const void *content,
					size_t pstart,
					size_t plen)
{
	t_btree	*found;

	if (!(found = ft_btree_searchm(bt, content, pstart, plen)))
		return (NULL);
	return (ft_btree_move(bt, found));
}
