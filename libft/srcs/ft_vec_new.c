/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:51:49 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/11 20:46:36 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_mem.h"
#include <stdarg.h>

t_vec	*ft_vec_new(size_t dimensions)
{
	t_vec	*vec;

	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->dimensions = dimensions;
	if (!(vec->vector = (float *)ft_memalloc(sizeof(float) * dimensions)))
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}

t_vec	*ft_vec_newf(size_t dimensions, float *vector)
{
	t_vec	*vec;

	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->dimensions = dimensions;
	if (!(vec->vector = (float *)ft_memdup((void *)vector,
					sizeof(float) * dimensions)))
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}

t_vec	*ft_vec_newi(size_t dimensions, float scalar)
{
	t_vec	*vec;
	size_t	i;

	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->dimensions = dimensions;
	if (!(vec->vector = (float *)malloc(sizeof(float) * dimensions)))
	{
		free(vec);
		return (NULL);
	}
	i = 0;
	while (i < dimensions)
	{
		vec->vector[i] = scalar;
		++i;
	}
	return (vec);
}

t_vec	*ft_vec_newn(size_t dimensions, ...)
{
	t_vec	*vec;
	size_t	i;
	va_list	vp;

	if (!(vec = (t_vec *)malloc(sizeof(t_vec))))
		return (NULL);
	vec->dimensions = dimensions;
	if (!(vec->vector = (float *)malloc(sizeof(float) * dimensions)))
	{
		free(vec);
		return (NULL);
	}
	va_start(vp, dimensions);
	i = 0;
	while (i < dimensions)
		vec->vector[i++] = (float)va_arg(vp, double);
	va_end(vp);
	return (vec);
}

void	ft_vec_del(t_vec **vec)
{
	if (!vec || !*vec)
		return ;
	free((*vec)->vector);
	free(*vec);
	*vec = NULL;
}
