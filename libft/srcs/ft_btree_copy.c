/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:27:35 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:39:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_copy(t_btree *bt)
{
	t_btree	*newbt;

	if (!bt)
		return (NULL);
	newbt = ft_btree_new(bt->content, bt->content_size);
	if ((newbt->left = ft_btree_copy(bt->left)))
		newbt->left->parent = newbt;
	if ((newbt->right = ft_btree_copy(bt->right)))
		newbt->right->parent = newbt;
	return (newbt);
}
