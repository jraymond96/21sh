/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstrp_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:28:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/17 21:58:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_math.h"
#include "ft_mem.h"
#include <stdarg.h>

int			ft_strpbrkstrp_len(const char *a, int type, size_t size, ...)
{
	va_list		vp;
	int			ret;

	if (!a)
		return (0);
	va_start(vp, size);
	ret = ft_strpbrkstrpv_len(a, type, size, vp);
	va_end(vp);
	return (ret);
}

int			ft_strpbrkstrpl_len(const char *a, int type, size_t size, ...)
{
	va_list		vp;
	int			ret;

	if (!a)
		return (0);
	va_start(vp, size);
	ret = ft_strpbrkstrplv_len(a, type, size, vp);
	va_end(vp);
	return (ret);
}
