/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:21:30 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/14 23:29:54 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include <stdlib.h>
#include "ft_printf.h"

t_mat	*ft_mat_opget(size_t rows, size_t columns, t_mat *res)
{
	if (!res && !(res = ft_mat_new(rows, columns)))
		return (NULL);
	if (res->rows != rows && res->columns != columns)
		if (!(res->matrix = (float *)malloc(sizeof(float)
						* (columns * rows))))
			return (NULL);
	res->rows = rows;
	res->columns = columns;
	return (res);
}

t_mat	*ft_mat_add(t_mat a, t_mat b, t_mat *res)
{
	size_t	i;
	size_t	size;

	if (a.columns != b.columns || a.rows != b.rows)
		return (NULL);
	res = ft_mat_opget(a.rows, b.columns, res);
	size = a.columns * b.rows;
	i = 0;
	while (i < size)
	{
		res->matrix[i] = a.matrix[i] + b.matrix[i];
		++i;
	}
	return (res);
}

t_mat	*ft_mat_addi(t_mat a, float b, t_mat *res)
{
	size_t	i;
	size_t	size;

	res = ft_mat_opget(a.rows, a.columns, res);
	size = a.rows * a.columns;
	i = 0;
	while (i < size)
	{
		res->matrix[i] = a.matrix[i] + b;
		++i;
	}
	return (res);
}

t_mat	*ft_mat_iadd(float a, t_mat b, t_mat *res)
{
	size_t	i;
	size_t	size;

	res = ft_mat_opget(b.rows, b.columns, res);
	size = b.rows * b.columns;
	i = 0;
	while (i < size)
	{
		res->matrix[i] = a + b.matrix[i];
		++i;
	}
	return (res);
}
