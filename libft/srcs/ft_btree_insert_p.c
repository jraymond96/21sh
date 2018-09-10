/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 21:14:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/28 17:29:41 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_insert_p(t_btree **bt, t_btree *elem)
{
	t_btree	*tmp;

	if (!bt)
		return (NULL);
	tmp = ft_btree_insert(*bt, elem);
	if (!*bt)
		*bt = tmp;
	return (elem);
}

t_btree	*ft_btree_insertf_p(t_btree **bt, t_btree *elem, t_cmpfunc cmp)
{
	t_btree	*tmp;

	if (!bt)
		return (NULL);
	tmp = ft_btree_insertf(*bt, elem, cmp);
	if (!*bt)
		*bt = tmp;
	return (tmp);
}

t_btree	*ft_btree_insertm_p(t_btree **bt, t_btree *elem, size_t pstart,
						size_t plen)
{
	t_btree	*tmp;

	if (!bt)
		return (NULL);
	tmp = ft_btree_insertm(*bt, elem, pstart, plen);
	if (!*bt)
		*bt = tmp;
	return (elem);
}
