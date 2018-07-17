/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:31:26 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:27:15 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_wstrlen(const wchar_t *wcs)
{
	int	i;

	i = 0;
	while (*wcs)
		i += ft_wcharlen(*wcs++);
	return (i);
}

int	ft_wstrnlen(const wchar_t *wstr, int n)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (wstr)
	{
		while (*wstr && i + len <= n)
		{
			if ((len = ft_wcharlen(*wstr++)) == 0)
				return (-1);
			if (i + len > n)
				return (i);
			i += len;
		}
	}
	return (i);
}
