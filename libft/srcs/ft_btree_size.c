/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:25:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/02 20:44:14 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_math.h"

size_t	ft_btree_size(t_btree *bt)
{
	if (bt)
		return (1 + ft_btree_size(bt->left) + ft_btree_size(bt->right));
	return (0);
}

size_t	ft_btree_depth(t_btree *bt)
{
	if (bt)
	{
		return (1 + ft_max(ft_btree_depth(bt->left),
					ft_btree_depth(bt->right)));
	}
	return (0);
}
