/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:48:50 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/31 21:08:16 by jraymond         ###   ########.fr       */
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
