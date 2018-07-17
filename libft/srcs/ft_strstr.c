/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:07:59 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:41:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strstr(const char *a, const char *b)
{
	size_t	j;

	while (*a)
	{
		j = 0;
		while (b[j] && a[j] && (b[j] == a[j]))
			++j;
		if (b[j] == '\0')
			return ((char *)a);
		++a;
	}
	return (NULL);
}

char	*ft_strnstr(const char *a, const char *b, size_t n)
{
	size_t	blen;

	if (*a == '\0' || n == 0)
		return (NULL);
	if (*b == '\0')
		return ((char *)a);
	blen = ft_strlen(b);
	while (*a && n-- >= blen)
	{
		if (ft_strncmp(a, b, blen) == 0)
			return ((char *)(a));
		++a;
	}
	return (NULL);
}

char	*ft_strrstr(const char *a, const char *b)
{
	int		i;
	int		j;
	size_t	blen;

	i = ft_strlen(a);
	blen = ft_strlen(b) - 1;
	while (--i >= 0)
	{
		j = blen;
		while (j >= 0 && a[i - (blen - j)] && (a[i - (blen - j)] == b[j]))
			--j;
		if (j == 0)
			return ((char *)(&a[i]));
	}
	return (NULL);
}

int		ft_strstr_pos(const char *a, const char *b)
{
	int		pos;
	size_t	j;

	if (!a || !b)
		return (-1);
	pos = 0;
	while (a[pos])
	{
		j = 0;
		while (b[j] && a[pos + j] && (b[j] == a[pos + j]))
			++j;
		if (b[j] == '\0')
			return (pos);
		++pos;
	}
	return (-1);
}

int		ft_strstrl_pos(const char *a, const char *b)
{
	int		pos;
	size_t	j;

	if (!a || !b)
		return (-1);
	pos = 0;
	while (a[pos])
	{
		if (a[pos] == '\\' && ++pos)
			if (!a[pos++])
				return (-1);
		j = 0;
		while (b[j] && a[pos + j] && (b[j] == a[pos + j]))
			++j;
		if (b[j] == '\0')
			return (pos);
		++pos;
	}
	return (-1);
}
