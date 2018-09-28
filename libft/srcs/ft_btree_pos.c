/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 21:04:03 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 22:37:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	ft_btree_pos(t_btree *bt, t_btree *elem)
{
	if (!elem || !bt)
		return (0);
	if (elem->parent == bt)
		return (elem == bt->left ? -1 : 1);
	return (ft_btree_pos(bt, elem->parent));
}
