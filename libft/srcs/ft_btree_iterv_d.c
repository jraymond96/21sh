/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iterv_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:30:31 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/20 17:03:27 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

static void	inner_btree_lov(t_btree *bt, t_btiter_d f, int nm[2], void *data)
{
	if (!bt)
		return ;
	if (nm[0] == nm[1])
		return (f(bt, data));
	nm[0] += 1;
	inner_btree_lov(bt->right, f, nm, data);
	inner_btree_lov(bt->left, f, nm, data);
}

static void	ft_btree_levelorderv(t_btree *bt, t_btiter_d f, void *data)
{
	int	n;
	int	i;
	int	nm[2];

	n = ft_btree_depth(bt);
	i = 0;
	while (i < n)
	{
		nm[0] = 0;
		nm[1] = i++;
		inner_btree_lov(bt, f, nm, data);
	}
}

void		ft_btree_itermv_d(t_btree *bt, t_btiter_d f, t_btmode mode,
						void *data)
{
	if (!bt || !f)
		return ;
	if (mode == BT_LEVELORDER)
		return (ft_btree_levelorderv(bt, f, data));
	if (mode == BT_PREORDER)
		f(bt, data);
	ft_btree_itermv_d(bt->right, f, mode, data);
	if (mode == BT_INORDER)
		f(bt, data);
	ft_btree_itermv_d(bt->left, f, mode, data);
	if (mode == BT_POSTORDER)
		f(bt, data);
}

void		ft_btree_iterv_d(t_btree *bt, t_btiter_d f, void *data)
{
	ft_btree_itermv_d(bt, f, BT_INORDER, data);
}
