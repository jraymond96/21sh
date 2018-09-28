/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:05:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/11 16:06:00 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memstr(const void *a, size_t an, const void *b, size_t ab)
{
	size_t	i;

	i = 0;
	while (i < an)
	{
		if (i + ab <= an && ft_memcmp((const char *)a + i, b, ab) == 0)
			return ((char *)a + i);
		++i;
	}
	return (NULL);
}

int		ft_memstr_pos(const void *a, size_t an, const void *b, size_t ab)
{
	size_t	i;

	i = 0;
	while (i < an)
	{
		if (i + ab <= an && ft_memcmp((const char *)a + i, b, ab) == 0)
			return (i);
		++i;
	}
	return (-1);
}
