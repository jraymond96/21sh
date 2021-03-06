/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_tolist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:05:12 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/16 20:19:10 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_list			*ft_btree_tolist(t_btree *bt)
{
	return (ft_btree_tolistm(bt, BT_INORDER));
}

static t_list	*inner_btree_lo(t_btree *bt, int n, int m)
{
	t_list	*lst;
	t_list	*tmp;

	if (!bt)
		return (NULL);
	if (n == m)
		return (ft_lstcreate(bt->content, bt->content_size));
	lst = NULL;
	ft_lstpushfront(&lst, inner_btree_lo(bt->left, n + 1, m));
	tmp = ft_lstpush(lst, inner_btree_lo(bt->right, n + 1, m));
	if (!lst)
		lst = tmp;
	return (lst);
}

static t_list	*ft_btree_levelorder(t_btree *bt)
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
		tmp = ft_lstpush(lst, inner_btree_lo(bt, 0, i++));
		if (!lst)
			lst = tmp;
	}
	return (lst);
}

static t_list	*inner_btree_tolistm(t_btree *bt, t_btmode mode)
{
	t_list	*lst;
	t_list	*left;
	t_list	*right;

	if (!(lst = ft_lstnew(bt->content, bt->content_size)))
		return (NULL);
	left = ft_btree_tolistm(bt->left, mode);
	right = ft_btree_tolistm(bt->right, mode);
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

t_list			*ft_btree_tolistm(t_btree *bt, t_btmode mode)
{
	if (!bt)
		return (NULL);
	if (mode == BT_LEVELORDER)
		return (ft_btree_levelorder(bt));
	return (inner_btree_tolistm(bt, mode));
}
