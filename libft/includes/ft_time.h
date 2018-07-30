/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:50:05 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/18 17:01:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TIME_H
# define FT_TIME_H

# include <time.h>

typedef struct		s_timef
{
	unsigned int	hour;
	unsigned int	min;
	unsigned int	sec;
	unsigned int	day;
	unsigned int	month;
	unsigned int	year;
	char			*cday;
	char			*cmonth;
	time_t			full;
}					t_timef;

t_timef				*ft_timefnew(const time_t *t);
void				ft_timefdel(t_timef **tf);

#endif
