/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:08:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 17:07:21 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec	*ft_vec_opget(size_t dimensions, t_vec *res)
{
	if (!res && !(res = ft_vec_new(dimensions)))
		return (NULL);
	if (res->dimensions != dimensions)
		if (!(res->vector = (float *)malloc(sizeof(float) * dimensions)))
			return (NULL);
	res->dimensions = dimensions;
	return (res);
}

t_vec	*ft_vec_add(t_vec a, t_vec b, t_vec *res)
{
	size_t	i;
	size_t	dmin;

	dmin = ft_umin(a.dimensions, b.dimensions);
	res = ft_vec_opget(dmin, res);
	i = 0;
	while (i < dmin)
	{
		res->vector[i] = a.vector[i] + b.vector[i];
		++i;
	}
	return (res);
}

t_vec	*ft_vec_addi(t_vec a, float b, t_vec *res)
{
	size_t	i;

	res = ft_vec_opget(a.dimensions, res);
	i = 0;
	while (i < a.dimensions)
	{
		res->vector[i] = a.vector[i] + b;
		++i;
	}
	return (res);
}

t_vec	*ft_vec_iadd(float a, t_vec b, t_vec *res)
{
	size_t	i;

	res = ft_vec_opget(b.dimensions, res);
	i = 0;
	while (i < b.dimensions)
	{
		res->vector[i] = a + b.vector[i];
		++i;
	}
	return (res);
}
