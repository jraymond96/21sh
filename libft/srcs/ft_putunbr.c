/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:57:49 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:35:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

void	ft_putunbr(unsigned int n)
{
	ft_putunbr_fd(n, 1);
}

void	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n / 10 != 0)
		ft_putunbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + 48, fd);
}
