/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_fromlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:28:01 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/16 20:19:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_fromlistf(t_list *lst, t_cmpfunc cmp)
{
	t_btree	*bt;
	t_btree	*elem;

	bt = NULL;
	while (lst && cmp)
	{
		elem = ft_btree_create(lst->content, lst->content_size);
		elem = ft_btree_insertf(bt, elem, cmp);
		if (!bt)
			bt = elem;
		lst = lst->next;
	}
	return (bt);
}

t_btree	*ft_btree_fromlist(t_list *lst)
{
	return (ft_btree_fromlistf(lst, ft_memcmp));
}
