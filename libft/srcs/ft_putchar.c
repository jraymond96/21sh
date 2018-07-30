/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:21:43 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:24:21 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

void	ft_putchar(char c)
{
	ft_putchar_fd(c, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnchar(char c, size_t n)
{
	ft_putnchar_fd(c, n, 1);
}

void	ft_putnchar_fd(char c, size_t n, int fd)
{
	while (n--)
		ft_putchar_fd(c, fd);
}
