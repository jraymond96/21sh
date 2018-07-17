/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pevent_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:04:43 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:05:10 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"
#include "ft_mem.h"

static void	delevent(void *data, size_t n)
{
	(void)n;
	ft_event_del((t_event **)&data);
}

t_pevent	*ft_pevent_new(void)
{
	t_pevent	*event;

	if (!(event = ft_memalloc(sizeof(t_pevent))))
		return (NULL);
	return (event);
}

void		ft_pevent_del(t_pevent **event)
{
	if (event && *event)
		ft_btree_del(&(*event)->callbacks, delevent);
	ft_memdel((void **)event);
}
