/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:42:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/16 16:54:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdarg.h>

void	*ft_memdup(const void *s, size_t n)
{
	void	*mem;

	if (s && (mem = malloc(n)))
		return (ft_memcpy(mem, s, n));
	return (ft_memalloc(n));
}

void	**ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
	return (ap);
}

int		ft_memdel_x(size_t n, ...)
{
	size_t	i;
	va_list	vp;

	i = 0;
	va_start(vp, n);
	while (i++ < n)
		ft_memdel((void **)va_arg(vp, void **));
	va_end(vp);
	return (i);
}

int		ft_memdel_xp(size_t n, void **ptr)
{
	size_t	i;

	i = 0;
	while (i < n)
		ft_memdel(&ptr[i++]);
	return (i);
}

void	content_delfunc(void *a, size_t b)
{
	(void)b;
	free(a);
}
