/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 17:08:03 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 17:10:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVENT_H
# define FT_EVENT_H

# include "ft_list.h"
# include "ft_btree.h"

/*
** Simple event system, when the event is triggered all callbacks functions are
** called in the same order ther were added.
*/

typedef struct	s_event
{
	int			trigger;
	t_list		*callbacks;
}				t_event;

typedef void	(*t_callback)(t_event *event, void *data);

t_event			*ft_event_new(void);
void			ft_event_del(t_event **event);
void			ft_event_clean(t_event *event);

int				ft_event_add(t_event *event, t_callback callback);
int				ft_event_remove(t_event *event, t_callback callback);

void			ft_event_trigger(t_event *event, void *data);
void			ft_event_release(t_event *event);

/*
** A little bit different, callbacks are called depending on their priority
** channels. Callbacks on channel 0 are called first, then channel 1 etc.
** If callbacks are only added to the 0th channel, then it is the same as the
** the structure above.
*/

typedef struct	s_pevent
{
	int			trigger;
	t_btree		*callbacks;
}				t_pevent;

typedef void	(*t_pcallback)(t_pevent *event, void *data);

t_pevent		*ft_pevent_new(void);
void			ft_pevent_del(t_pevent **event);

/*
** Cleans all callbacks in the event.
** Cleans only callbacks on the given channel.
*/

void			ft_pevent_clean(t_pevent *event);
void			ft_pevent_cleanp(t_pevent *event, int chan);

int				ft_pevent_add(t_pevent *event, t_pcallback callback);
int				ft_pevent_addp(t_pevent *event,
						t_pcallback callback,
						int chan);
int				ft_pevent_remove(t_pevent *event, t_pcallback callback);
int				ft_pevent_removep(t_pevent *event,
						t_pcallback callback,
						int chan);

void			ft_pevent_trigger(t_pevent *event, void *data);
void			ft_pevent_release(t_pevent *event);

#endif
