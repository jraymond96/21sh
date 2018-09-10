/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 20:08:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:08:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char		*ft_strcatl(char *a, const char *b)
{
	size_t	i;
	int		n;

	n = 1;
	if (!a || !b)
		return (a);
	i = ft_strlen(a);
	while (*b)
	{
		if (*b == '\\' && n)
		{
			++b;
			n = 0;
		}
		else
		{
			n = 1;
			a[i++] = *b++;
		}
	}
	a[i] = '\0';
	return (a);
}

char		*ft_strncatl(char *a, const char *b, size_t n)
{
	size_t	i;
	size_t	j;
	int		u;

	if (!a || !b)
		return (a);
	i = ft_strlen(a);
	j = 0;
	u = 1;
	while (b[j] && j < n)
	{
		if (b[j] == '\\' && u)
			u = 0;
		else
		{
			u = 1;
			a[i++] = b[j];
		}
		++j;
	}
	a[i] = '\0';
	return (a);
}
