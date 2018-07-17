/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:42:02 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:07:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

int	ft_memcmp(const void *a, const void *b, size_t n)
{
	const unsigned char	*ca;
	const unsigned char	*cb;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	ca = (const unsigned char *)a;
	cb = (const unsigned char *)b;
	while (i < n - 1 && (ca[i] == cb[i]))
		++i;
	return ((int)(ca[i] - cb[i]));
}

int	ft_memccmp(const void *a, const void *b, int c, size_t n)
{
	const unsigned char	*ca;
	const unsigned char	*cb;
	unsigned char		cc;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	ca = (const unsigned char *)a;
	cb = (const unsigned char *)b;
	cc = (unsigned char)c;
	while (i < n - 1 && ca[i] != cc && cb[i] != cc && (ca[i] == cb[i]))
		++i;
	return ((int)(ca[i] - cb[i]));
}
