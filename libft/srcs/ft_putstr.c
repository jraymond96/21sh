/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:21:00 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:49:43 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"

void	ft_putstr(const char *s)
{
	ft_putstr_fd(s, 1);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnstr(const char *s, size_t n)
{
	ft_putnstr_fd(s, n, 1);
}

void	ft_putnstr_fd(const char *s, size_t n, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] && i < n)
		ft_putchar_fd(s[i++], fd);
}
