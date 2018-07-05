/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:48:50 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/14 18:18:43 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list	*ft_lstend(t_list *lst)
{
	if (lst && lst->next)
		return (ft_lstend(lst->next));
	return (lst);
}

t_list	*ft_lstparent(t_list *lst)
{
	if (lst && lst->parent)
		return (ft_lstparent(lst->parent));
	return (lst);
}
