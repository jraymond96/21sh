/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:15 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:07:25 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

int	ft_lstcount(t_list *lst, const void *content, size_t content_size)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while ((tmp = ft_lstfind(tmp, content, content_size)))
	{
		++count;
		tmp = tmp->next;
	}
	return (count);
}

int	ft_lstcountf(t_list *lst, const void *content, size_t content_size,
			t_cmpfunc cmp)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while ((tmp = ft_lstfindf(tmp, content, content_size, cmp)))
	{
		++count;
		tmp = tmp->next;
	}
	return (count);
}

int	ft_lstcountm(t_list *lst, const void *content, size_t pstart, size_t plen)
{
	t_list	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while ((tmp = ft_lstfindm(tmp, content, pstart, plen)))
	{
		++count;
		tmp = tmp->next;
	}
	return (count);
}
