/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:56:12 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/08 16:23:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strdupli(const char *s)
{
	size_t	i;
	char	*str;

	if (!s || !(str = ft_strnew(ft_strlenl(s))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == '\\')
		{
			if (*++s)
				++s;
		}
		else
			str[i++] = *s++;
	}
	return (str);
}

char		*ft_strndupli(const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	int		u;
	char	*str;

	if (!s || !(str = ft_strnew(ft_strlenl(s))))
		return (NULL);
	i = 0;
	j = 0;
	u = 1;
	while (s[j] && j < n)
	{
		if (s[j] == '\\' && u)
			u = 0;
		else
		{
			u = 1;
			str[i++] = s[j];
		}
		++j;
	}
	return (str);
}
