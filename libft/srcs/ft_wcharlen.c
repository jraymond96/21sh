/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:06:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/23 20:55:17 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_wcharlen(wchar_t c)
{
	if (c < 0 || (c >= 0xd800 && c < 0xe000))
		return (0);
	if ((c <= 0x7f && MB_CUR_MAX >= 1) || (c <= 0xff && MB_CUR_MAX == 1))
		return (1);
	else if (c <= 0x7ff && MB_CUR_MAX >= 2)
		return (2);
	else if (c <= 0xffff && MB_CUR_MAX >= 3)
		return (3);
	else if (c <= 0x10ffff && MB_CUR_MAX >= 4)
		return (4);
	return (0);
}
