/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrln.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:56:25 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/16 21:56:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strchrln(const char *a, int c)
{
	return (ft_strnchrln(a, c, ft_strlen(a)));
}

int		ft_strchrln_pos(const char *a, int c)
{
	return (ft_strnchrln_pos(a, c, ft_strlen(a)));
}

char	*ft_strnchrln(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a[i] == '\\' && ++i)
		{
			if (a[i] == c)
				return ((char *)&a[i]);
			else if (!a[i])
				return (NULL);
		}
		else if (a[i] == c)
			break ;
		++i;
	}
	return ((char *)(i == n ? NULL : &a[i]));
}

int		ft_strnchrln_pos(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a[i] == '\\' && ++i)
		{
			if (a[i] == c)
				return (i);
			else if (!a[i])
				return (-1);
		}
		else if (a[i] == c)
			break ;
		++i;
	}
	return (i == n ? -1 : (int)i);
}
