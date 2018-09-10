/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsterase_all.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:01 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:07:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lsterase_all(t_list **lst, const void *content, size_t content_size)
{
	t_list	*erased_lst;
	t_list	*tmp;

	erased_lst = NULL;
	while ((tmp = ft_lsterase(lst, content, content_size)))
	{
		if (erased_lst)
			ft_lstpush(erased_lst, tmp);
		else
			erased_lst = tmp;
	}
	return (erased_lst);
}

t_list	*ft_lsterasef_all(t_list **lst, const void *content,
					size_t content_size, t_cmpfunc cmp)
{
	t_list	*erased_lst;
	t_list	*tmp;

	erased_lst = NULL;
	while ((tmp = ft_lsterasef(lst, content, content_size, cmp)))
	{
		if (erased_lst)
			ft_lstpush(erased_lst, tmp);
		else
			erased_lst = tmp;
	}
	return (erased_lst);
}

t_list	*ft_lsterasem_all(t_list **lst, const void *content, size_t pstart,
						size_t plen)
{
	t_list	*erased_lst;
	t_list	*tmp;

	erased_lst = NULL;
	while ((tmp = ft_lsterasem(lst, content, pstart, plen)))
	{
		if (erased_lst)
			ft_lstpush(erased_lst, tmp);
		else
			erased_lst = tmp;
	}
	return (erased_lst);
}
