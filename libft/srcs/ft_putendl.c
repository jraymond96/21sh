/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:22:14 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:26:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"

void	ft_putendl(const char *s)
{
	ft_putendl_fd(s, 1);
}

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnendl(const char *s, size_t n)
{
	ft_putnendl_fd(s, n, 1);
}

void	ft_putnendl_fd(const char *s, size_t n, int fd)
{
	ft_putnstr_fd(s, n, fd);
	ft_putchar_fd('\n', fd);
}
