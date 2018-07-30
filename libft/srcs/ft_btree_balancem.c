/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_balancem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:59:24 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 17:12:24 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

static t_btree	*ft_btree_alignm(t_btree *bt, t_ptrpos ptrpos)
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
		return (bt == (bt_rot = ft_btree_leftrotatem(bt, ptrpos.start,
			ptrpos.len)) ? bt_rot : ft_btree_alignm(bt_rot, ptrpos));
	}
	else if (pos == 1 && rightlen < leftlen)
	{
		return (bt == (bt_rot = ft_btree_rightrotatem(bt, ptrpos.start,
			ptrpos.len)) ? bt_rot : ft_btree_alignm(bt_rot, ptrpos));
	}
	return (bt);
}

static t_btree	*inner_btree_balancem(t_btree *bt, t_ptrpos ptrpos)
{
	int			leftlen;
	int			rightlen;
	t_btree		*nr;

	if ((nr = ft_btree_alignm(bt, ptrpos)))
	{
		while (1)
		{
			balancem_childs(nr, &leftlen, &rightlen, ptrpos);
			if (!(leftlen < rightlen - 1) || nr == (bt = ft_btree_alignm(
				ft_btree_leftrotatem(nr, ptrpos.start, ptrpos.len), ptrpos)))
				break ;
			nr = bt;
		}
		while (1)
		{
			balancem_childs(nr, &leftlen, &rightlen, ptrpos);
			if (!(rightlen < leftlen - 1) || nr == (bt = ft_btree_alignm(
				ft_btree_rightrotatem(nr, ptrpos.start, ptrpos.len), ptrpos)))
				break ;
			nr = bt;
		}
	}
	return (nr);
}

void			balancem_childs(t_btree *bt, int *leftlen, int *rightlen,
						t_ptrpos ptrpos)
{
	bt->left = inner_btree_balancem(bt->left, ptrpos);
	bt->right = inner_btree_balancem(bt->right, ptrpos);
	*leftlen = ft_btree_size(bt->left);
	*rightlen = ft_btree_size(bt->right);
}

t_btree			*ft_btree_balancem(t_btree *bt, size_t start, size_t len)
{
	t_ptrpos ptrpos;

	ptrpos.start = start;
	ptrpos.len = len;
	return (inner_btree_balancem(bt, ptrpos));
}
