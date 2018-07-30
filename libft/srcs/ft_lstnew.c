/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:31:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/16 22:04:00 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		if (content)
		{
			if (!(lst->content = ft_memdup(content, content_size)))
			{
				free(lst);
				return (NULL);
			}
		}
		lst->content_size = (content ? content_size : 0);
	}
	return (lst);
}

t_list	*ft_lstcreate(void *content, size_t content_size)
{
	t_list	*lst;

	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))))
	{
		lst->content = content;
		lst->content_size = (content ? content_size : 0);
	}
	return (lst);
}

void	ft_lstdelv(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*nxt;

	nxt = (alst && *alst ? (*alst)->parent : NULL);
	ft_lstdelone(alst, del);
	if (nxt)
		ft_lstdelv(&nxt, del);
}

void	ft_lstdelv_d(t_list **alst, t_delfunc_d del, void *data)
{
	t_list	*nxt;

	nxt = (alst && *alst ? (*alst)->parent : NULL);
	ft_lstdelone_d(alst, del, data);
	if (nxt)
		ft_lstdelv_d(&nxt, del, data);
}
