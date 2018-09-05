/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:08:24 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/10 14:53:59 by mmerabet         ###   ########.fr       */
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
