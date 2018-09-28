/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsterase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:57:08 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 22:35:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstextract(t_list **alst, t_list *node)
{
	if (!node)
		return (node);
	if (node->parent)
		node->parent->next = node->next;
	else
		*alst = node->next;
	if (node->next)
		node->next->parent = node->parent;
	return (node);
}

t_list	*ft_lstconnect(t_list *a, t_list *b)
{
	if (!a || !b)
		return (NULL);
	a->next = b;
	b->parent = a;
	return (a);
}

t_list	*ft_lsterase(t_list **alst,
					const void *content,
					size_t content_size)
{
	t_list	*tmp;
	t_list	*lstdel;

	if (alst && (lstdel = ft_lstfind(*alst, content, content_size)))
	{
		if ((tmp = lstdel->parent))
		{
			if ((tmp->next = lstdel->next))
				lstdel->next->parent = tmp;
		}
		else if ((*alst)->next)
		{
			lstdel = (*alst)->next;
			if (((*alst)->next = lstdel->next))
				lstdel->next->parent = *alst;
			ft_lstswap(*alst, lstdel);
		}
		else
			*alst = NULL;
		lstdel->parent = NULL;
		lstdel->next = NULL;
		return (lstdel);
	}
	return (NULL);
}

t_list	*ft_lsterasef(t_list **alst,
					const void *content,
					size_t content_size,
					t_cmpfunc cmp)
{
	t_list	*tmp;
	t_list	*lstdel;

	if (alst && (lstdel = ft_lstfindf(*alst, content, content_size, cmp)))
	{
		if ((tmp = lstdel->parent))
		{
			if ((tmp->next = lstdel->next))
				lstdel->next->parent = tmp;
		}
		else if ((*alst)->next)
		{
			lstdel = (*alst)->next;
			if (((*alst)->next = lstdel->next))
				lstdel->next->parent = *alst;
			ft_lstswap(*alst, lstdel);
		}
		else
			*alst = NULL;
		lstdel->parent = NULL;
		lstdel->next = NULL;
		return (lstdel);
	}
	return (NULL);
}

t_list	*ft_lsterasem(t_list **alst,
					const void *content,
					size_t pstart,
					size_t plen)
{
	t_list	*tmp;
	t_list	*lstdel;

	if (alst && (lstdel = ft_lstfindm(*alst, content, pstart, plen)))
	{
		if ((tmp = lstdel->parent))
		{
			if ((tmp->next = lstdel->next))
				lstdel->next->parent = tmp;
		}
		else if ((*alst)->next)
		{
			lstdel = (*alst)->next;
			if (((*alst)->next = lstdel->next))
				lstdel->next->parent = *alst;
			ft_lstswap(*alst, lstdel);
		}
		else
			*alst = NULL;
		lstdel->parent = NULL;
		lstdel->next = NULL;
		return (lstdel);
	}
	return (NULL);
}
