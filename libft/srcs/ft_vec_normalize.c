/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:31:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/15 18:29:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

float	ft_vec_length(t_vec *vec)
{
	return (sqrtf(ft_vec_lengthb(vec)));
}

float	ft_vec_lengthb(t_vec *vec)
{
	float	len;
	size_t	i;

	len = 0.f;
	if (!vec || !vec->vector)
		return (len);
	i = 0;
	while (i < vec->dimensions)
	{
		len += (vec->vector[i] * vec->vector[i]);
		++i;
	}
	return (len);
}

t_vec	*ft_vec_normalize(t_vec vec, t_vec *res)
{
	float	len;
	size_t	i;

	if (!(res = ft_vec_opget(vec.dimensions, res)))
		return (NULL);
	len = ft_vec_length(&vec);
	i = 0;
	while (i < res->dimensions)
		res->vector[i++] /= len;
	return (res);
}

t_vec	*ft_vec_cross(t_vec a, t_vec b, t_vec *res)
{
	if (a.dimensions != 3 || b.dimensions != 3 || !(res = ft_vec_opget(3, res)))
		return (NULL);
	res->vector[0] = a.vector[1] * b.vector[2] - b.vector[1] * a.vector[2];
	res->vector[1] = a.vector[2] * b.vector[0] - b.vector[2] * a.vector[0];
	res->vector[2] = a.vector[0] * b.vector[1] - b.vector[0] * a.vector[1];
	return (res);
}

float	ft_vec_dot(t_vec *a, t_vec *b)
{
	float	dot;
	size_t	i;

	dot = 0.f;
	if (!a || !a->vector || !b || !b->vector || a->dimensions != b->dimensions)
		return (dot);
	i = 0;
	while (i < a->dimensions)
	{
		dot += a->vector[i] * b->vector[i];
		++i;
	}
	return (dot);
}
