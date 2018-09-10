/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 12:44:56 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/15 19:03:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"

t_list	*ft_lstfind(t_list *lst, const void *content, size_t content_size)
{
	if (!lst)
		return (NULL);
	if (lst->content_size == content_size)
		if (ft_memcmp(lst->content, content, content_size) == 0)
			return (lst);
	return (ft_lstfind(lst->next, content, content_size));
}

t_list	*ft_lstfindf(t_list *lst, const void *content, size_t content_size,
				t_cmpfunc cmp)
{
	if (!lst || !cmp)
		return (NULL);
	if (cmp(lst->content, content, content_size) == 0)
		return (lst);
	return (ft_lstfindf(lst->next, content, content_size, cmp));
}

t_list	*ft_lstfindm(t_list *lst,
				const void *content,
				size_t pstart,
				size_t plen)
{
	if (!lst)
		return (NULL);
	if (ft_memcmp(lst->content + pstart, content + pstart, plen) == 0)
		return (lst);
	return (ft_lstfindm(lst->next, content, pstart, plen));
}
