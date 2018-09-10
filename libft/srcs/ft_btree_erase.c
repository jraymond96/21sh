/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_erase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:22:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:53:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

static t_btree	*ft_btree_erase_case(t_btree *found, int d)
{
	t_btree	*tmp;

	if (d == 0)
	{
		tmp = (found->left ? found->left : found->right);
		ft_btree_swap(found, tmp, 1);
	}
	else if (d == 1)
	{
		tmp = ft_btree_left(found->right);
		if (tmp->parent == found)
			tmp->parent->right = tmp->right;
		else
			tmp->parent->left = tmp->right;
		ft_btree_swap(found, tmp, 0);
	}
	else
	{
		if (found->parent && found == found->parent->left)
			found->parent->left = NULL;
		else if (found->parent)
			found->parent->right = NULL;
		tmp = found;
	}
	return (tmp);
}

t_btree			*ft_btree_erase(t_btree **bt,
							const void *content,
							size_t content_size)
{
	return (ft_btree_erasef(bt, content, content_size, ft_memcmp));
}

t_btree			*ft_btree_erasef(t_btree **bt,
					const void *content,
					size_t content_size,
					t_cmpfunc cmp)
{
	int		cmp_n;
	t_btree	*tmp;

	tmp = NULL;
	if (!bt || !*bt || !cmp)
		return (NULL);
	cmp_n = cmp((*bt)->content, content, content_size);
	if (cmp_n > 0)
		return (ft_btree_erasef(&(*bt)->left, content, content_size, cmp));
	else if (cmp_n < 0)
		return (ft_btree_erasef(&(*bt)->right, content, content_size, cmp));
	else
	{
		if (((*bt)->right && !(*bt)->left) || (!(*bt)->right && (*bt)->left))
			tmp = ft_btree_erase_case(*bt, 0);
		else if ((*bt)->right && (*bt)->left)
			tmp = ft_btree_erase_case(*bt, 1);
		else
			tmp = ft_btree_erase_case(*bt, 2);
		if (!tmp->left && !tmp->right && !tmp->parent)
			*bt = NULL;
		ft_bzero((char *)tmp + (sizeof(void *) + sizeof(size_t)),
				sizeof(t_btree *) * 3);
	}
	return (tmp);
}

t_btree			*ft_btree_erasem(t_btree **bt,
					const void *content,
					size_t pstart,
					size_t plen)
{
	int		cmp_n;
	t_btree	*tmp;

	tmp = NULL;
	if (!bt || !*bt)
		return (NULL);
	cmp_n = ft_memcmp((*bt)->content + pstart, content + pstart, plen);
	if (cmp_n > 0)
		return (ft_btree_erasem(&(*bt)->left, content, pstart, plen));
	else if (cmp_n < 0)
		return (ft_btree_erasem(&(*bt)->right, content, pstart, plen));
	else
	{
		if (((*bt)->right && !(*bt)->left) || (!(*bt)->right && (*bt)->left))
			tmp = ft_btree_erase_case(*bt, 0);
		else if ((*bt)->right && (*bt)->left)
			tmp = ft_btree_erase_case(*bt, 1);
		else
			tmp = ft_btree_erase_case(*bt, 2);
		if (!tmp->left && !tmp->right && !tmp->parent)
			*bt = NULL;
		ft_bzero((char *)tmp + (sizeof(void *) + sizeof(size_t)),
				sizeof(t_btree *) * 3);
	}
	return (tmp);
}
