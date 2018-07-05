/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:46:40 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:50:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_strcount(const char *s, char a)
{
	int	count;

	count = 0;
	while (s && *s)
		if (*s++ == a)
			++count;
	return (count);
}

int	ft_strcountstr(const char *s, const char *a)
{
	int	count;
	int	j;

	count = 0;
	while (s && *s)
	{
		j = 0;
		while (a[j] && s[j] && (a[j] == s[j]))
			++j;
		if (a[j] == '\0')
			++count;
		++s;
	}
	return (count);
}
