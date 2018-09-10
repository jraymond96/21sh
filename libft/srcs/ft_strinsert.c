/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 21:06:26 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/06 21:30:59 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

char	*ft_strinsert(char *a, char *b, size_t start, size_t size)
{
	size_t	i;
	size_t	len;

	if (start > (len = ft_strlen(a)))
		return (a);
	len += size;
	while (len >= start + size)
	{
		a[len] = a[len - size];
		--len;
	}
	i = 0;
	while (i < size)
		a[start++] = b[i++];
	return (a);
}

char	*ft_strerase(char *a, size_t start, size_t n)
{
	size_t	i;
	size_t	len;

	if (start > (len = ft_strlen(a)))
		return (a);
	i = start;
	while (i + n < len)
	{
		a[i] = a[i + n];
		++i;
	}
	while (i < len)
		a[i++] = '\0';
	return (a);
}
