/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:08:24 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/12 23:07:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstpush(t_list *lst, t_list *elem)
{
	t_list	*lst_end;

	if ((lst_end = ft_lstend(lst)))
		if ((lst_end->next = elem))
			elem->parent = lst_end;
	return (elem);
}

t_list	*ft_lstpush_p(t_list **lst, t_list *elem)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = ft_lstpush(*lst, elem);
	if (!*lst)
		*lst = tmp;
	return (tmp);
}

void	ft_lstpushfront(t_list **alst, t_list *elem)
{
	t_list	*lst_end;

	if (alst && elem)
	{
		lst_end = ft_lstend(elem);
		if ((lst_end->next = *alst))
			(*alst)->parent = lst_end;
		*alst = elem;
	}
}

void	ft_lstadd(t_list **alst, t_list *elem)
{
	if (alst && elem)
	{
		if ((elem->next = *alst))
			(*alst)->parent = elem;
		*alst = elem;
	}
}

t_list	*ft_lstinsert(t_list **alst, t_list *elem, int invert)
{
	t_list	*tmp;
	t_list	*end;

	end = ft_lstend(elem);
	if (!*alst)
	{
		*alst = elem;
		return (end);
	}
	if (invert && (end->next = *alst))
	{
		if ((tmp = (*alst)->parent))
			ft_lstconnect(tmp, elem);
		(*alst)->parent = end;
	}
	else if ((elem->parent = *alst))
	{
		if ((tmp = (*alst)->next))
			ft_lstconnect(end, tmp);
		(*alst)->next = elem;
	}
	return (end);
}
