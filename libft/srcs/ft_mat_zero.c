/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 21:03:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:16:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"

t_mat	*ft_mat_zero(t_mat *mat)
{
	size_t	i;
	size_t	size;

	if (!mat || !mat->matrix)
		return (mat);
	i = 0;
	size = mat->rows * mat->columns;
	while (i < size)
	{
		mat->matrix[i] = 0.0;
		++i;
	}
	return (mat);
}

t_mat	*ft_mat_copy(t_mat *dst, t_mat *src)
{
	size_t	i;
	size_t	asize;
	size_t	bsize;

	if (!dst || !dst->matrix || !src || !src->matrix)
		return (dst);
	i = 0;
	asize = dst->rows * dst->columns;
	bsize = src->rows * src->columns;
	while (i < asize && i < bsize)
	{
		dst->matrix[i] = src->matrix[i];
		++i;
	}
	return (src);
}

t_mat	*ft_mat_dup(t_mat *src)
{
	if (!src)
		return (NULL);
	return (ft_mat_newf(src->rows, src->columns, src->matrix));
}
