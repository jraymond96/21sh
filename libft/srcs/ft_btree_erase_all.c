/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_erase_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:54:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:55:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_erase_all(t_btree **bt, const void *content,
						size_t content_size)
{
	t_btree	*erased_bt;
	t_btree	*tmp;
	t_btree	*right;

	erased_bt = NULL;
	if (!bt)
		return (NULL);
	while ((tmp = ft_btree_erase(bt, content, content_size)))
	{
		if (!erased_bt)
			erased_bt = tmp;
		else
		{
			right = ft_btree_right(erased_bt);
			right->right = tmp;
			tmp->parent = right;
		}
	}
	return (erased_bt);
}

t_btree	*ft_btree_erasef_all(t_btree **bt, const void *content,
						size_t content_size, t_cmpfunc cmp)
{
	t_btree	*erased_bt;
	t_btree	*tmp;
	t_btree	*right;

	erased_bt = NULL;
	if (!bt)
		return (NULL);
	while ((tmp = ft_btree_erasef(bt, content, content_size, cmp)))
	{
		if (!erased_bt)
			erased_bt = tmp;
		else
		{
			right = ft_btree_right(erased_bt);
			right->right = tmp;
			tmp->parent = right;
		}
	}
	return (erased_bt);
}

t_btree	*ft_btree_erasem_all(t_btree **bt, const void *content, size_t pstart,
						size_t plen)
{
	t_btree	*erased_bt;
	t_btree	*tmp;
	t_btree	*right;

	erased_bt = NULL;
	if (!bt)
		return (NULL);
	while ((tmp = ft_btree_erasem(bt, content, pstart, plen)))
	{
		if (!erased_bt)
			erased_bt = tmp;
		else
		{
			right = ft_btree_right(erased_bt);
			right->right = tmp;
			tmp->parent = right;
		}
	}
	return (erased_bt);
}
