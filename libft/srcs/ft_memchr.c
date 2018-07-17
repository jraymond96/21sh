/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:41:57 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/29 11:51:27 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	cc;
	size_t			i;

	i = 0;
	cs = (unsigned char *)s;
	cc = (unsigned char)c;
	while (i++ < n)
		if (*cs++ == cc)
			return ((void *)(cs - 1));
	return (NULL);
}

int		ft_memchr_pos(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	cc;
	size_t			i;

	i = -1;
	cs = (unsigned char *)s;
	cc = (unsigned char)c;
	while (++i < n)
		if (*cs++ == cc)
			return (i);
	return (-1);
}
