/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:39:42 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:01:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec	*ft_vec_sub(t_vec a, t_vec b, t_vec *res)
{
	size_t	i;
	size_t	dmin;

	dmin = ft_umin(a.dimensions, b.dimensions);
	res = ft_vec_opget(dmin, res);
	i = 0;
	while (i < dmin)
	{
		res->vector[i] = a.vector[i] - b.vector[i];
		++i;
	}
	return (res);
}

t_vec	*ft_vec_subi(t_vec a, float b, t_vec *res)
{
	size_t	i;

	res = ft_vec_opget(a.dimensions, res);
	i = 0;
	while (i < a.dimensions)
	{
		res->vector[i] = a.vector[i] - b;
		++i;
	}
	return (res);
}

t_vec	*ft_vec_isub(float a, t_vec b, t_vec *res)
{
	size_t	i;

	res = ft_vec_opget(b.dimensions, res);
	i = 0;
	while (i < b.dimensions)
	{
		res->vector[i] = a - b.vector[i];
		++i;
	}
	return (res);
}
