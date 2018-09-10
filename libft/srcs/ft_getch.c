/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:48:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:20:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include <stdlib.h>

int	ft_getch(void)
{
	int				r;
	unsigned char	c;

	if ((r = read(0, &c, sizeof(unsigned char))) < 0)
		return (r);
	return (c);
}

int	ft_getwch(void)
{
	int	c;

	if (((c = ft_getch()) <= 0x7f && MB_CUR_MAX >= 1)
			|| (c <= 0xff && MB_CUR_MAX == 1))
		return (c);
	else if (c <= 0x7ff && MB_CUR_MAX >= 2)
		return (c | ft_getch());
	else if (c <= 0xffff && MB_CUR_MAX >= 3)
		return (c | ft_getch() | ft_getch());
	else if (c <= 0x10ffff && MB_CUR_MAX >= 4)
		return (c | ft_getch() | ft_getch() | ft_getch());
	return (c);
}
