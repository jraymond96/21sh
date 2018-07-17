/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 21:01:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:01:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec	*ft_vec_zero(t_vec *vec)
{
	size_t	i;

	if (!vec || !vec->vector)
		return (vec);
	i = 0;
	while (i < vec->dimensions)
	{
		vec->vector[i] = 0.0;
		++i;
	}
	return (vec);
}

t_vec	*ft_vec_copy(t_vec *dst, t_vec *src)
{
	size_t	i;

	if (!dst || !dst->vector || !src || !src->vector)
		return (dst);
	i = 0;
	while (i < dst->dimensions && i < src->dimensions)
	{
		dst->vector[i] = src->vector[i];
		++i;
	}
	return (dst);
}

t_vec	*ft_vec_dup(t_vec *src)
{
	if (!src)
		return (NULL);
	return (ft_vec_newf(src->dimensions, src->vector));
}
