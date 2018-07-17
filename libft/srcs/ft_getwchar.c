/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:09:26 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/14 16:47:05 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

static char	*inner_getwchar(wchar_t wc, char wcs[MB_CUR_MAX + 1])
{
	if ((wc <= 0x7f && MB_CUR_MAX >= 1) || (wc <= 0xff && MB_CUR_MAX == 1))
		wcs[0] = (char)wc;
	else if (wc <= 0x7ff && MB_CUR_MAX >= 2)
	{
		wcs[0] = (char)((wc >> 6) | 0xc0);
		wcs[1] = (char)((wc & 0x3f) | 0x80);
	}
	else if (wc <= 0xffff && MB_CUR_MAX >= 3)
	{
		wcs[0] = (char)((wc >> 12) | 0xe0);
		wcs[1] = (char)(((wc >> 6) & 0x3f) | 0x80);
		wcs[2] = (char)((wc & 0x3f) | 0x80);
	}
	else if (wc <= 0x10ffff && MB_CUR_MAX >= 4)
	{
		wcs[0] = (char)((wc >> 18) | 0xf0);
		wcs[1] = (char)(((wc >> 12) & 0x3f) | 0x80);
		wcs[2] = (char)(((wc >> 6) & 0x3f) | 0x80);
		wcs[3] = (char)((wc & 0x3f) | 0x80);
	}
	return (ft_strdup(wcs));
}

char		*ft_getwchar(wchar_t wc)
{
	char	wcs[MB_CUR_MAX + 1];

	if (ft_wcharlen(wc) == 0)
		return (NULL);
	ft_bzero(wcs, MB_CUR_MAX + 1);
	return (inner_getwchar(wc, wcs));
}
