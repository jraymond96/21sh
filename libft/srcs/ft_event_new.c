/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:07:44 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"
#include "ft_mem.h"

t_event	*ft_event_new(void)
{
	t_event	*event;

	if (!(event = ft_memalloc(sizeof(t_event))))
		return (NULL);
	return (event);
}

void	ft_event_del(t_event **event)
{
	if (event && *event)
		ft_lstdel(&(*event)->callbacks, NULL);
	ft_memdel((void **)event);
}
