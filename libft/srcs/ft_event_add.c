/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:08:26 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:08:31 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"

static int	cmpcall(const void *a, const void *b, size_t n)
{
	(void)n;
	return (a - b);
}

int			ft_event_add(t_event *event, t_callback callback)
{
	t_list	*lst;

	if (!event || !callback)
		return (0);
	if (!(lst = ft_lstpush(event->callbacks,
		ft_lstcreate(callback, sizeof(t_callback)))))
		return (0);
	if (!event->callbacks)
		event->callbacks = lst;
	return (1);
}

int			ft_event_remove(t_event *event, t_callback callback)
{
	t_list	*lst;

	if (!event || !callback || !(lst =
		ft_lsterasef_all(&event->callbacks, callback, sizeof(t_callback),
			cmpcall)))
		return (0);
	ft_lstdel(&lst, NULL);
	return (1);
}
