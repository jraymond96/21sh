/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 12:37:16 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:38:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstcopy(t_list *lst)
{
	return (ft_lstmap(lst, ft_lstcopyone));
}

t_list	*ft_lstcopyone(t_list *lst)
{
	if (!lst)
		return (NULL);
	return (ft_lstnew(lst->content, lst->content_size));
}
