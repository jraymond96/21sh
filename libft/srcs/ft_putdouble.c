/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:35:05 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:21:29 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

void	ft_putdouble(double n, int precision)
{
	ft_putdouble_fd(n, precision, 1);
}

void	ft_putdouble_fd(double n, int precision, int fd)
{
	int		i;
	int		firstp;
	double	secondp;
	double	precision_adder;

	firstp = (int)n;
	secondp = (double)(n - firstp) * (n < 0 ? -1 : 1);
	ft_putnbr_fd(firstp, fd);
	if (precision > 0)
	{
		ft_putchar_fd('.', fd);
		precision_adder = 0.1;
		i = 0;
		while (i++ < precision)
			precision_adder /= 10;
		secondp += precision_adder;
		while (--i)
		{
			ft_putnbr_fd((int)(secondp *= 10), fd);
			firstp = (int)secondp;
			secondp -= (double)firstp;
		}
	}
}
