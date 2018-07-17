/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 19:26:35 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:03:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"

t_mat	*ft_mat_div(t_mat a, t_mat b, t_mat *res)
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
		res->matrix[i] = a.matrix[i] / b.matrix[i];
		++i;
	}
	return (res);
}

t_mat	*ft_mat_divi(t_mat a, float b, t_mat *res)
{
	size_t	i;
	size_t	size;

	res = ft_mat_opget(a.rows, a.columns, res);
	size = a.rows * a.columns;
	i = 0;
	while (i < size)
	{
		res->matrix[i] = a.matrix[i] / b;
		++i;
	}
	return (res);
}

t_mat	*ft_mat_idiv(float a, t_mat b, t_mat *res)
{
	size_t	i;
	size_t	size;

	res = ft_mat_opget(b.rows, b.columns, res);
	size = b.rows * b.columns;
	i = 0;
	while (i < size)
	{
		res->matrix[i] = a / b.matrix[i];
		++i;
	}
	return (res);
}
