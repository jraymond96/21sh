/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:22:00 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/06 04:42:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

char	*ft_strclr(char *s)
{
	if (s)
		ft_bzero((void *)s, ft_strlen(s));
	return (s);
}

char	*ft_strnclr(char *s, size_t n)
{
	size_t	l;

	l = ft_strlen(s);
	if (n > l)
		n = l;
	if (s)
		ft_bzero((void *)s, n);
	return (s);
}

char	*ft_strend(const char *str)
{
	char	*it;

	it = (char *)str;
	if (!*it)
		return (it);
	while (*(it + 1))
		++it;
	return (it);
}
