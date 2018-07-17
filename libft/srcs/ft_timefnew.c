/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timefnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:47:44 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 15:00:48 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_time.h"
#include "ft_types.h"
#include "ft_str.h"
#include "ft_mem.h"

static unsigned int	timef_getmonth(const char *mth)
{
	static char	*mths[] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"
	};
	int			i;

	if (!mth)
		return (0);
	i = -1;
	while (++i < 12)
		if (ft_strequ(mth, mths[i]))
			return (i + 1);
	return (0);
}

t_timef				*ft_timefnew(const time_t *t)
{
	t_timef	*tf;
	char	*out;
	time_t	cur_t;

	if (!t && (cur_t = time(NULL)))
		return (ft_timefnew(&cur_t));
	if (!(tf = ft_memalloc(sizeof(t_timef))))
		return (NULL);
	if (!(out = ctime(t)))
	{
		free(tf);
		return (NULL);
	}
	tf->hour = ft_atoui(out + 11);
	tf->min = ft_atoui(out + 14);
	tf->sec = ft_atoui(out + 17);
	tf->day = ft_atoui(out + 8);
	tf->year = ft_atoui(out + 20);
	tf->cday = ft_strndup(out, 3);
	tf->cmonth = ft_strndup(out + 4, 3);
	tf->month = timef_getmonth(tf->cmonth);
	tf->full = *t;
	return (tf);
}

void				ft_timefdel(t_timef **tf)
{
	if (!tf || !*tf)
		return ;
	free((*tf)->cday);
	free((*tf)->cmonth);
	free(*tf);
	*tf = NULL;
}
