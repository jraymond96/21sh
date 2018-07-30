/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 21:24:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/13 15:58:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include "ft_printf.h"
#include "ft_mem.h"

t_mat	*ft_mat_mult(t_mat a, t_mat b, t_mat *res)
{
	size_t		i[3];
	float		*tmp;

	if (a.columns != b.rows || !(res = ft_mat_opget(a.rows, b.columns, res)))
		return (NULL);
	tmp = res->matrix;
	if ((tmp == a.matrix || tmp == b.matrix) && !(res->matrix =
				(float *)malloc(sizeof(float) * (a.rows * b.columns))))
		res->matrix = tmp;
	i[0] = -1;
	while (++i[0] < a.rows)
	{
		i[1] = -1;
		while (++i[1] < b.columns)
		{
			*ft_mat_get(res, i[1], i[0]) = 0.f;
			i[2] = -1;
			while (++i[2] < a.columns)
				*ft_mat_get(res, i[1], i[0]) +=
					*ft_mat_get(&a, i[2], i[0]) * *ft_mat_get(&b, i[1], i[2]);
		}
	}
	if ((tmp == a.matrix || tmp == b.matrix) && tmp != res->matrix)
		free(tmp);
	return (res);
}

t_mat	*ft_mat_multi(t_mat a, float b, t_mat *res)
{
	size_t	i;
	size_t	size;

	if (!res || res->matrix != a.matrix)
		res = ft_mat_opget(a.rows, a.columns, res);
	i = 0;
	size = a.rows * a.columns;
	while (i < size)
	{
		res->matrix[i] = a.matrix[i] * b;
		++i;
	}
	return (res);
}

t_mat	*ft_mat_imult(float a, t_mat b, t_mat *res)
{
	size_t	i;
	size_t	size;

	if (!res || res->matrix != b.matrix)
		res = ft_mat_opget(b.rows, b.columns, res);
	i = 0;
	size = b.rows * b.columns;
	while (i < size)
	{
		res->matrix[i] = a * b.matrix[i];
		++i;
	}
	return (res);
}

t_vec	*ft_mat_multv(t_mat a, t_vec b, t_vec *res)
{
	size_t	i[2];
	float	*tmp;

	tmp = NULL;
	if (a.columns != b.dimensions)
		return (NULL);
	if (res && res->vector == b.vector)
	{
		res->dimensions = a.rows;
		tmp = res->vector;
		if (!(res->vector = (float *)malloc(sizeof(float) * a.rows)))
			res->vector = b.vector;
	}
	else
		res = ft_vec_opget(a.rows, res);
	i[0] = -1;
	while (++i[0] < a.rows)
	{
		res->vector[i[0]] = 0.f;
		i[1] = -1;
		while (++i[1] < a.columns)
			res->vector[i[0]] += *ft_mat_get(&a, i[1], i[0]) * b.vector[i[1]];
	}
	free(tmp);
	return (res);
}

t_vec	*ft_mat_vmult(t_vec a, t_mat b, t_vec *res)
{
	size_t	i[2];
	float	*tmp;

	tmp = NULL;
	if (b.columns != a.dimensions)
		return (NULL);
	if (res && res->vector == a.vector)
	{
		res->dimensions = b.rows;
		tmp = res->vector;
		if (!(res->vector = (float *)malloc(sizeof(float) * b.rows)))
			res->vector = a.vector;
	}
	else
		res = ft_vec_opget(b.rows, res);
	i[0] = -1;
	while (++i[0] < b.rows)
	{
		res->vector[i[0]] = 0.f;
		i[1] = -1;
		while (++i[1] < b.columns)
			res->vector[i[0]] += a.vector[i[1]] * *ft_mat_get(&b, i[1], i[0]);
	}
	free(tmp);
	return (res);
}
