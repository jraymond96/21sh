/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 20:24:47 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/19 17:52:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"

t_list	*ft_lstsort(t_list *lst)
{
	return (ft_lstsortf(lst, ft_memcmp));
}

t_list	*ft_lstsortf(t_list *lst, t_cmpfunc cmp)
{
	t_list	*lst_a;
	t_list	*lst_b;

	lst_a = lst;
	while (lst_a)
	{
		lst_b = lst_a->next;
		while (lst_b)
		{
			if (cmp(lst_a->content, lst_b->content, lst_b->content_size) > 0)
				ft_lstswap(lst_a, lst_b);
			lst_b = lst_b->next;
		}
		lst_a = lst_a->next;
	}
	return (lst);
}

t_list	*ft_lstsortv(t_list *lst)
{
	return (ft_lstsortvf(lst, ft_memcmp));
}

t_list	*ft_lstsortvf(t_list *lst, t_cmpfunc cmp)
{
	t_list	*lst_a;
	t_list	*lst_b;

	lst_a = lst;
	while (lst_a)
	{
		lst_b = lst_a->next;
		while (lst_b)
		{
			if (cmp(lst_a->content, lst_b->content, lst_b->content_size) < 0)
				ft_lstswap(lst_a, lst_b);
			lst_b = lst_b->next;
		}
		lst_a = lst_a->next;
	}
	return (lst);
}
