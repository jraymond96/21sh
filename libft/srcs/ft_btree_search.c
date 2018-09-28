/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:58:49 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 21:53:49 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_searchf(t_btree *bt,
					const void *content,
					size_t content_size,
					t_cmpfunc cmp)
{
	int	cmp_n;

	if (!cmp)
		return (NULL);
	while (bt)
	{
		cmp_n = cmp(bt->content, content, content_size);
		if (cmp_n == 0)
			return (bt);
		bt = (cmp_n < 0 ? bt->right : bt->left);
	}
	return (bt);
}

t_btree	*ft_btree_searchm(t_btree *bt,
						const void *content,
						size_t pstart,
						size_t plen)
{
	int	cmp_n;

	if (!bt)
		return (NULL);
	while (bt)
	{
		cmp_n = ft_memcmp(bt->content + pstart, content + pstart, plen);
		if (!cmp_n)
			return (bt);
		bt = (cmp_n < 0 ? bt->right : bt->left);
	}
	return (bt);
}

t_btree	*ft_btree_search(t_btree *bt, const void *content, size_t content_size)
{
	return (ft_btree_searchf(bt, content, content_size, ft_memcmp));
}
