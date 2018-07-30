/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_tolistv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:53 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:07:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_list			*ft_btree_tolistv(t_btree *bt)
{
	return (ft_btree_tolistmv(bt, BT_INORDER));
}

static t_list	*inner_btree_lov(t_btree *bt, int n, int m)
{
	t_list	*lst;
	t_list	*tmp;

	if (!bt)
		return (NULL);
	if (n == m)
		return (ft_lstnew(bt->content, bt->content_size));
	lst = NULL;
	ft_lstpushfront(&lst, inner_btree_lov(bt->right, n + 1, m));
	tmp = ft_lstpush(lst, inner_btree_lov(bt->left, n + 1, m));
	if (!lst)
		lst = tmp;
	return (lst);
}

static t_list	*ft_btree_levelorderv(t_btree *bt)
{
	t_list	*lst;
	t_list	*tmp;
	int		n;
	int		i;

	lst = NULL;
	n = ft_btree_depth(bt);
	i = 0;
	while (i < n)
	{
		tmp = ft_lstpush(lst, inner_btree_lov(bt, 0, i++));
		if (!lst)
			lst = tmp;
	}
	return (lst);
}

static t_list	*inner_btree_tolistmv(t_btree *bt, t_btmode mode)
{
	t_list	*lst;
	t_list	*left;
	t_list	*right;

	if (!(lst = ft_lstnew(bt->content, bt->content_size)))
		return (NULL);
	left = ft_btree_tolistmv(bt->right, mode);
	right = ft_btree_tolistmv(bt->left, mode);
	if (mode == BT_INORDER || mode == BT_POSTORDER)
		ft_lstpushfront(&lst, (mode == BT_INORDER ? left : right));
	else if (mode == BT_PREORDER)
		ft_lstpush(lst, left);
	if (mode == BT_INORDER || mode == BT_PREORDER)
		ft_lstpush(lst, right);
	else if (mode == BT_POSTORDER)
		ft_lstpushfront(&lst, left);
	return (lst);
}

t_list			*ft_btree_tolistmv(t_btree *bt, t_btmode mode)
{
	if (!bt)
		return (NULL);
	if (mode == BT_LEVELORDER)
		return (ft_btree_levelorderv(bt));
	return (inner_btree_tolistmv(bt, mode));
}
