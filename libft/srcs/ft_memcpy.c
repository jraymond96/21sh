/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:42:19 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/22 15:10:10 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			i;

	i = 0;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (i < n)
		cdst[i++] = *csrc++;
	return (dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*cdst;
	const unsigned char	*csrc;

	cdst = (unsigned char *)dst;
	csrc = (const unsigned char *)src;
	while (n--)
		if ((*cdst++ = *csrc++) == (unsigned char)c)
			return (cdst);
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*cdst;
	const char	*csrc;

	if (dst <= src)
		ft_memcpy(dst, src, n);
	else
	{
		cdst = dst + n - 1;
		csrc = src + n - 1;
		while (n--)
			*cdst-- = *csrc--;
	}
	return (dst);
}
