/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:19:41 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:13:13 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_math.h"

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n <= -10)
			ft_putnbr_fd(-(n / 10), fd);
	}
	else if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(ft_abs(n % 10) + 48, fd);
}

void	ft_putnbr_base(int n, const char *base)
{
	ft_putnbr_base_fd(n, base, 1);
}

void	ft_putnbr_base_fd(int n, const char *base, int fd)
{
	int	baselen;

	if (!base)
		return ;
	baselen = ft_strlen(base);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_base_fd(-(n / baselen), base, fd);
	}
	else if (n / baselen != 0)
		ft_putnbr_base_fd(n / baselen, base, fd);
	ft_putchar_fd(base[ft_abs((int)n % baselen)], fd);
}
