/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:45:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/16 14:39:54 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strchrl(const char *a, int c)
{
	return (ft_strnchrl(a, c, ft_strlen(a)));
}

int		ft_strchrl_pos(const char *a, int c)
{
	return (ft_strnchrl_pos(a, c, ft_strlen(a)));
}

char	*ft_strnchrl(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a[i] == '\\')
		{
			if (!a[++i])
				return (NULL);
		}
		else if (a[i] == c)
			break ;
		++i;
	}
	return ((char *)(i == n ? NULL : &a[i]));
}

int		ft_strnchrl_pos(const char *a, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (a[i] == '\\')
		{
			if (!a[++i])
				return (-1);
		}
		else if (a[i] == c)
			break ;
		++i;
	}
	return (i == n ? -1 : (int)i);
}
