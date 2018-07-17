/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pevent_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:06:43 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:19:13 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"

int	ft_pevent_add(t_pevent *event, t_pcallback callback)
{
	return (ft_pevent_addp(event, callback, 0));
}

int	ft_pevent_addp(t_pevent *event, t_pcallback callback, int chan)
{
	t_btree		*bt;
	t_event		ev;

	if (!event || !callback)
		return (0);
	ev.trigger = chan;
	ev.callbacks = NULL;
	if (!(bt = ft_btree_getnewm(event->callbacks, &ev, sizeof(t_event),
		make_ptrpos(0, sizeof(int)))))
		return (0);
	if (!event->callbacks)
		event->callbacks = bt;
	if (!ft_event_add((t_event *)bt->content, (t_callback)callback))
		return (0);
	return (1);
}
