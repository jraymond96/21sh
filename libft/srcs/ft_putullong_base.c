/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putullong_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:55:52 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:50:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"

void	ft_putullong_base(unsigned long long n, const char *base)
{
	ft_putullong_base_fd(n, base, 1);
}

void	ft_putullong_base_fd(unsigned long long n, const char *base, int fd)
{
	int	baselen;

	if (!base)
		return ;
	baselen = ft_strlen(base);
	if (n / baselen != 0)
		ft_putullong_base_fd(n / baselen, base, fd);
	ft_putchar_fd(base[n % baselen], fd);
}
