/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:12:56 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/07 17:40:27 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"

static long double	ft_ldtoa_adder(int precision)
{
	long double	adder;

	adder = (precision ? 0.05 : 0.5);
	while (precision-- > 1)
		adder /= 10;
	return (adder);
}

static double		ft_dtoa_adder(int precision)
{
	double	adder;

	adder = (precision ? 0.05 : 0.5);
	while (precision-- > 1)
		adder /= 10;
	return (adder);
}

char				*ft_dtoa(double n, int precision)
{
	long long	firstp;
	double		secondp;
	char		*cps[2];
	int			kprec;

	kprec = 0;
	firstp = (long long)(n + ft_dtoa_adder(precision));
	secondp = (double)(n - firstp) * (n < 0 ? -1 : 1);
	cps[0] = ft_lltoa(firstp);
	if (precision > 0)
	{
		cps[1] = ft_strnew(precision);
		secondp += ft_dtoa_adder(precision);
		while (kprec < precision)
		{
			secondp *= 10;
			cps[1][kprec++] = ((unsigned long long)secondp % 10) + 48;
		}
		cps[0] = ft_strjoin_clr(ft_strjoinc_clr(cps[0], '.'), cps[1], 2);
	}
	return (cps[0]);
}

char				*ft_ldtoa(long double n, int precision)
{
	long long	firstp;
	long double	secondp;
	char		*cps[2];
	int			kprec;

	kprec = 0;
	firstp = (long long)(n + (ft_ldtoa_adder(precision) * (n < 0 ? -1 : 1)));
	secondp = (long double)(n - firstp) * (n < 0 ? -1 : 1);
	cps[0] = ft_lltoa(firstp);
	if (precision > 0)
	{
		cps[1] = ft_strnew(precision);
		secondp += ft_ldtoa_adder(precision);
		while (kprec < precision)
		{
			secondp *= 10;
			cps[1][kprec++] = ((unsigned long long)secondp % 10) + 48;
			secondp -= (unsigned long long)(secondp / 10) * 10;
		}
		cps[0] = ft_strjoin_clr(ft_strjoinc_clr(cps[0], '.'), cps[1], 2);
	}
	return (cps[0]);
}
