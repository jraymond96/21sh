/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_balance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:07:10 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 17:02:53 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

static void		balance_childs(t_btree *bt, int *leftlen, int *rightlen,
						t_cmpfunc cmp)
{
	bt->left = ft_btree_balancef(bt->left, cmp);
	bt->right = ft_btree_balancef(bt->right, cmp);
	*leftlen = ft_btree_size(bt->left);
	*rightlen = ft_btree_size(bt->right);
}

static t_btree	*ft_btree_alignf(t_btree *bt, t_cmpfunc cmp)
{
	int		pos;
	int		leftlen;
	int		rightlen;
	t_btree	*bt_rot;

	if (!bt)
		return (NULL);
	leftlen = ft_btree_size(bt->left);
	rightlen = ft_btree_size(bt->right);
	if ((pos = ft_btree_pos(bt->parent, bt)) == -1 && leftlen < rightlen)
	{
		return (bt == (bt_rot = ft_btree_leftrotatef(bt, cmp)) ?
			bt_rot : ft_btree_alignf(bt_rot, cmp));
	}
	else if (pos == 1 && rightlen < leftlen)
	{
		return (bt == (bt_rot = ft_btree_rightrotatef(bt, cmp)) ?
			bt_rot : ft_btree_alignf(bt_rot, cmp));
	}
	return (bt);
}

t_btree			*ft_btree_balance(t_btree *bt)
{
	return (ft_btree_balancef(bt, ft_memcmp));
}

t_btree			*ft_btree_balancef(t_btree *bt, t_cmpfunc cmp)
{
	int		leftlen;
	int		rightlen;
	t_btree	*newroot;

	if ((newroot = ft_btree_alignf(bt, cmp)))
	{
		while (1)
		{
			balance_childs(newroot, &leftlen, &rightlen, cmp);
			if (leftlen >= rightlen - 1 || newroot == (bt = ft_btree_alignf(
				ft_btree_leftrotatef(newroot, cmp), cmp)))
				break ;
			newroot = bt;
		}
		while (1)
		{
			balance_childs(newroot, &leftlen, &rightlen, cmp);
			if (rightlen >= leftlen - 1 || newroot == (bt = ft_btree_alignf(
				ft_btree_rightrotatef(newroot, cmp), cmp)))
				break ;
			newroot = bt;
		}
	}
	return (newroot);
}
