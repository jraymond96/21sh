/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 23:30:35 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 23:32:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_root(t_btree *bt)
{
	if (!bt || !bt->parent)
		return (bt);
	return (ft_btree_root(bt->parent));
}
