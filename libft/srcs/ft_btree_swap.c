/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:10:42 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 19:35:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

void	ft_btree_swap(t_btree *a, t_btree *b, int childs)
{
	size_t	tmp;
	void	*ptr;

	if (a && b)
	{
		tmp = a->content_size;
		a->content_size = b->content_size;
		b->content_size = tmp;
		ptr = a->content;
		a->content = b->content;
		b->content = ptr;
		if (childs)
		{
			ft_swapptr((void **)&a->left, (void **)&b->left);
			if (a->left)
				a->left->parent = a;
			if (b->left)
				b->left->parent = b;
			ft_swapptr((void **)&a->right, (void **)&b->right);
			if (a->right)
				a->right->parent = a;
			if (b->right)
				b->right->parent = b;
		}
	}
}
