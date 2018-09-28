/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:14:01 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 15:12:17 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	if ((mem = malloc(size)))
		ft_bzero(mem, size);
	return (mem);
}

void	**ft_memalloc_xp(size_t n, size_t size, void **ptr)
{
	size_t	i;

	i = 0;
	while (i < n)
		if (!(ptr[i++] = ft_memalloc(size)))
			return (NULL);
	return (ptr);
}
