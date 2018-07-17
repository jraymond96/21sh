/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:04:49 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:24:46 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"

long long	ft_atoll(const char *s)
{
	long long	nb;
	int			sign;

	if (!s)
		return (0);
	nb = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1;
	while (ft_isdigit(*s))
		nb = nb * 10 + (*s++ - 48);
	return (nb * sign);
}

long long	ft_atoll_base(const char *s, const char *base)
{
	long long	nb;
	int			baselen;
	int			sign;
	int			pos;
	int			i;

	if (!s || !base)
		return (0);
	baselen = ft_strlen(base);
	i = ft_strlen(s);
	nb = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1;
	while ((pos = ft_strchr_pos(base, *s++)) != -1)
		nb += (long long)(pos * ft_pow(baselen, --i));
	return (nb * sign);
}
