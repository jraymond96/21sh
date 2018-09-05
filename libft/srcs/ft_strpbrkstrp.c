/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstrp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 18:14:39 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:13:56 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include <stdarg.h>

static int	end_va(va_list vp)
{
	va_end(vp);
	return (1);
}

int			ft_strpbrkstrp_pos(const char *a, int type, size_t size, ...)
{
	int		pos;
	int		len;
	va_list	vp;

	if (!a)
		return (0);
	pos = -1;
	len = 0;
	while (a[++pos])
	{
		va_start(vp, size);
		if ((len = ft_strpbrkstrpv_len(&a[pos], type, size, vp)) && end_va(vp))
			break ;
		va_end(vp);
	}
	g_iread = len;
	return (len ? pos : -1);
}

int			ft_strpbrkstrpl_pos(const char *a, int type, size_t size, ...)
{
	int		pos;
	int		len;
	va_list	vp;

	if (!a)
		return (0);
	pos = -1;
	len = 0;
	while (a[++pos])
	{
		va_start(vp, size);
		while (a[pos] == '\\' && ++pos)
			if ((!a[pos] || !a[++pos]) && end_va(vp))
				return (-1);
		if ((len = ft_strpbrkstrplv_len(&a[pos], type, size, vp)) && end_va(vp))
			break ;
		va_end(vp);
	}
	g_iread = len;
	return (len ? pos : -1);
}
