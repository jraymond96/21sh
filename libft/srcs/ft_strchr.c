/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:23:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/27 15:43:53 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (*s && *s != cc)
		++s;
	return ((char *)((*s == '\0' && cc != '\0') ? NULL : s));
}

char	*ft_strrchr(const char *s, int c)
{
	char	*pos;

	pos = (char *)s + ft_strlen(s);
	while (pos >= s)
	{
		if (*pos == c)
			return (pos);
		--pos;
	}
	return (NULL);
}

int		ft_strrchr_pos(const char *s, int c)
{
	int	pos;

	pos = (int)ft_strlen(s);
	while (--pos >= 0)
		if (s[pos] == c)
			return (pos);
	return (-1);
}

char	*ft_strnchr(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && a[i] != c)
		++i;
	return ((char *)(i == n ? NULL : &a[i]));
}

int		ft_strchr_pos(const char *s, int c)
{
	int	pos;

	if (!s)
		return (-1);
	pos = 0;
	while (s[pos] && s[pos] != c)
		++pos;
	return ((s[pos] == '\0') ? -1 : pos);
}
