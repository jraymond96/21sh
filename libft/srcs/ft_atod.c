/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:54:12 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 19:24:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"

double	ft_atod(const char *s)
{
	long long	firstp;
	double		secondp;
	char		*csecondp;

	if (!s)
		return (0.0);
	firstp = ft_atoll(s);
	if (!(csecondp = ft_strchr(s, '.')))
		return ((double)firstp - (firstp < 0 ? 1 : 0));
	else
		++csecondp;
	secondp = (double)ft_atoull(csecondp);
	while ((unsigned long long)secondp > 0 || *csecondp++ == '0')
		secondp /= 10;
	return (((double)ft_abs(firstp) + secondp) * (firstp < 0 ? -1 : 1));
}
