/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pevent_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:02:57 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:19:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_event.h"

static int	btiter(t_btree *bt, t_callback callback, int prev)
{
	if (!bt)
		return (0);
	if (btiter(bt->left, callback, prev))
		prev = 1;
	if (ft_event_remove((t_event *)bt->content, callback))
		prev = 1;
	if (btiter(bt->right, callback, prev))
		prev = 1;
	return (prev);
}

int			ft_pevent_remove(t_pevent *event, t_pcallback callback)
{
	if (!event)
		return (0);
	return (btiter(event->callbacks, (t_callback)callback, 0));
}

int			ft_pevent_removep(t_pevent *event, t_pcallback callback, int chan)
{
	t_btree	*bt;

	if (!event)
		return (0);
	if (!(bt = ft_btree_searchm(event->callbacks, &chan, 0, sizeof(int))))
		return (0);
	return (ft_event_remove((t_event *)bt->content, (t_callback)callback));
}
