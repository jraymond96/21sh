/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstrp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:14:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/11 15:28:48 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include <stdarg.h>

int	ft_strpbrkstrp_pos(const char *a, const void *data, size_t size, ...)
{
	int	pos;
	int	len;
	va_list	vp;
	size_t	as;
	size_t	bs;

	if (!data || !a)
		return (0);
	va_start(vp, size);
	as = va_arg(vp, size_t);
	bs = va_arg(vp, size_t);
	va_end(vp);
	pos = -1;
	while (a[++pos])
		if ((len = ft_strpbrkstrp_len(&a[pos], data, size, as, bs)))
			return ((g_iread = len) ? pos : pos);
	return (-1);
}

int	g_iread;

int	ft_strpbrkstrpl_pos(const char *a, const void *data, size_t size, ...)
{
	int	pos;
	int	len;
	va_list	vp;
	size_t	as;
	size_t	bs;

	if (!data || !a)
		return (0);
	va_start(vp, size);
	as = va_arg(vp, size_t);
	bs = va_arg(vp, size_t);
	va_end(vp);
	pos = -1;
	len = 0;
	while (a[++pos])
	{
		while (a[pos] == '\\' && ++pos)
			if (!a[pos] || !a[++pos])
				return (-1);
		if ((len = ft_strpbrkstrpl_len(&a[pos], data, size, as, bs)))
			break ;
	}
	g_iread = len;
	return (len ? pos : -1);
}
