/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:36:07 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/28 16:09:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int	ft_strequ(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	while (*a || *b)
		if (*a++ != *b++)
			return (0);
	return (1);
}

int	ft_strnequ(const char *a, const char *b, size_t n)
{
	if (!a || !b)
		return (0);
	while (n-- && (*a || *b))
		if (*a++ != *b++)
			return (0);
	return (1);
}

int	ft_strequl(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	while (*a || *b)
	{
		if (*a == '\\' && *++a)
			++a;
		if (*b == '\\' && *++b)
			++b;
		if (*a++ != *b++)
			return (0);
	}
	return (1);
}

int	ft_strnequl(const char *a, const char *b, size_t n)
{
	if (!a || !b)
		return (0);
	while (n-- && (*a || *b))
	{
		if (*a == '\\' && *++a)
			++a;
		if (*b == '\\' && *++b)
			++b;
		if (*a++ != *b++)
			return (0);
	}
	return (1);
}

int	ft_strequ_x(const char *a, const char *strset)
{
	int	pos;
	int	len;

	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')))
		{
			++strset;
			continue ;
		}
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (ft_strnequ(a, strset, len))
			return (1);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (0);
}
