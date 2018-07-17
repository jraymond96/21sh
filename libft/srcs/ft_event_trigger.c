/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_trigger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:07:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"

void	ft_event_trigger(t_event *event, void *data)
{
	t_list	*lst;

	if (!event)
		return ;
	lst = event->callbacks;
	event->trigger = 1;
	while (lst && event->trigger)
	{
		if (lst->content)
			((t_callback)lst->content)(event, data);
		lst = lst->next;
	}
	event->trigger = 0;
}

void	ft_event_release(t_event *event)
{
	if (event)
		event->trigger = 0;
}
