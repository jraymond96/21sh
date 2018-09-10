/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:31:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/18 17:29:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "ft_mem.h"

t_btree	*ft_btree_new(const void *content, size_t content_size)
{
	t_btree	*bt;

	if ((bt = (t_btree *)ft_memalloc(sizeof(t_btree))))
	{
		if (content)
			bt->content = ft_memdup(content, content_size);
		bt->content_size = (content ? content_size : 0);
	}
	return (bt);
}

t_btree	*ft_btree_create(void *content, size_t content_size)
{
	t_btree	*bt;

	if ((bt = (t_btree *)ft_memalloc(sizeof(t_btree))))
	{
		bt->content = content;
		bt->content_size = (content ? content_size : 0);
	}
	return (bt);
}

void	ft_btree_del(t_btree **abt, t_delfunc del)
{
	t_btree	*left;
	t_btree *right;

	left = NULL;
	right = NULL;
	if (abt && *abt)
	{
		left = (*abt)->left;
		right = (*abt)->right;
		ft_btree_delone(abt, del);
		if (left)
			ft_btree_del(&left, del);
		if (right)
			ft_btree_del(&right, del);
	}
}

void	ft_btree_delone(t_btree **abt, t_delfunc del)
{
	if (abt && *abt)
	{
		if (del)
			del((*abt)->content, (*abt)->content_size);
		ft_memdel((void **)abt);
	}
}
