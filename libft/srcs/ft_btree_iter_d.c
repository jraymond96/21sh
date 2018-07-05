/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_iter_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:18:05 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 22:35:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

static void	inner_btree_lo(t_btree *bt, t_btiter_d f, int nm[2], void *data)
{
	if (!bt)
		return ;
	if (nm[0] == nm[1])
		return (f(bt, data));
	nm[0] += 1;
	inner_btree_lo(bt->left, f, nm, data);
	inner_btree_lo(bt->right, f, nm, data);
}

static void	ft_btree_levelorder(t_btree *bt, t_btiter_d f, void *data)
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
		inner_btree_lo(bt, f, nm, data);
	}
}

void		ft_btree_iterm_d(t_btree *bt, t_btiter_d f, t_btmode mode,
						void *data)
{
	if (!bt || !f)
		return ;
	if (mode == BT_LEVELORDER)
		return (ft_btree_levelorder(bt, f, data));
	if (mode == BT_PREORDER)
		f(bt, data);
	ft_btree_iterm_d(bt->left, f, mode, data);
	if (mode == BT_INORDER)
		f(bt, data);
	ft_btree_iterm_d(bt->right, f, mode, data);
	if (mode == BT_POSTORDER)
		f(bt, data);
}

void		ft_btree_iter_d(t_btree *bt, t_btiter_d f, void *data)
{
	ft_btree_iterm_d(bt, f, BT_INORDER, data);
}
