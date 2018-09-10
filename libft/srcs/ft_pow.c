/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 16:34:46 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:27:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int			ft_pow(int x, int y)
{
	int	res;

	res = 1;
	while (y--)
		res *= x;
	return (res);
}

long long	ft_powl(long long x, long long y)
{
	long long	res;

	res = 1;
	while (y--)
		res *= x;
	return (res);
}

double		ft_fpow(double x, int y)
{
	double	res;
	double	exp;

	res = 1.0;
	if (y < 0)
	{
		exp = res / x;
		y = -y;
	}
	else
		exp = x;
	while (y > 0)
	{
		if (y & 1)
			res *= exp;
		exp *= exp;
		y >>= 1;
	}
	return (res);
}
