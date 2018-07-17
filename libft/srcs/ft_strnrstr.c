/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:06:46 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:49:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strnrstr(const char *a, const char *b, size_t n)
{
	int		i;
	int		j;
	size_t	alen;
	int		blen;

	if (!a || !b)
		return (NULL);
	alen = ft_strlen(a);
	if (n >= alen)
		n = alen - 1;
	i = n;
	blen = ft_strlen(b) - 1;
	while (i >= 0)
	{
		j = blen;
		while (b[j] && a[i - (blen - j)] && (a[i - (blen - j)] == b[j]))
			--j;
		if (j == 0)
			return ((char *)(&a[i]));
		--i;
	}
	return (NULL);
}
