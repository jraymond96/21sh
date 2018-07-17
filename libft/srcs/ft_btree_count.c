/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:54:50 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:54:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	ft_btree_count(t_btree *bt, const void *content, size_t content_size)
{
	t_btree	*tmp;
	int		count;

	tmp = bt;
	count = 0;
	while ((tmp = ft_btree_search(tmp, content, content_size)))
	{
		++count;
		tmp = tmp->right;
	}
	return (count);
}

int	ft_btree_countf(t_btree *bt, const void *content, size_t content_size,
				t_cmpfunc cmp)
{
	t_btree	*tmp;
	int		count;

	tmp = bt;
	count = 0;
	while ((tmp = ft_btree_searchf(tmp, content, content_size, cmp)))
	{
		++count;
		tmp = tmp->right;
	}
	return (count);
}

int	ft_btree_countm(t_btree *bt, const void *content, size_t pstart,
				size_t plen)
{
	t_btree	*tmp;
	int		count;

	tmp = bt;
	count = 0;
	while ((tmp = ft_btree_searchm(tmp, content, pstart, plen)))
	{
		++count;
		tmp = tmp->right;
	}
	return (count);
}
