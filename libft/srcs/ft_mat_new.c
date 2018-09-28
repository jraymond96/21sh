/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:44:01 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/15 16:26:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include "ft_mem.h"
#include <stdarg.h>

t_mat	*ft_mat_new(size_t rows, size_t columns)
{
	t_mat	*nmat;
	size_t	i;

	if (!(nmat = (t_mat *)malloc(sizeof(t_mat))))
		return (NULL);
	nmat->columns = columns;
	nmat->rows = rows;
	columns *= rows;
	if (!(nmat->matrix = (float *)malloc(sizeof(float) * columns)))
	{
		free(nmat);
		return (NULL);
	}
	i = 0;
	while (i < columns)
		nmat->matrix[i++] = 0.f;
	return (nmat);
}

t_mat	*ft_mat_newf(size_t rows, size_t columns, float *matrix)
{
	t_mat	*nmat;

	if (!(nmat = (t_mat *)malloc(sizeof(t_mat))))
		return (NULL);
	nmat->columns = columns;
	nmat->rows = rows;
	columns *= rows;
	if (!(nmat->matrix = (float *)ft_memdup((void *)matrix,
					sizeof(float) * columns)))
	{
		free(nmat);
		return (NULL);
	}
	return (nmat);
}

t_mat	*ft_mat_newi(size_t rows, size_t columns, float scalar)
{
	t_mat	*nmat;
	size_t	i;

	if (!(nmat = (t_mat *)malloc(sizeof(t_mat))))
		return (NULL);
	nmat->columns = columns;
	nmat->rows = rows;
	columns *= rows;
	if (!(nmat->matrix = (float *)malloc(sizeof(float) * columns)))
	{
		free(nmat);
		return (nmat);
	}
	i = 0;
	while (i < columns)
	{
		if ((nmat->columns == nmat->rows && i % (rows + 1) == 0)
				|| nmat->columns != nmat->rows)
			nmat->matrix[i] = scalar;
		else
			nmat->matrix[i] = 0.0f;
		++i;
	}
	return (nmat);
}

t_mat	*ft_mat_newn(size_t rows, size_t columns, ...)
{
	va_list	vp;
	t_mat	*nmat;
	size_t	i;

	if (!(nmat = (t_mat *)malloc(sizeof(t_mat))))
		return (NULL);
	nmat->columns = columns;
	nmat->rows = rows;
	columns *= rows;
	if (!(nmat->matrix = (float *)malloc(sizeof(float) * columns)))
	{
		free(nmat);
		return (nmat);
	}
	i = 0;
	va_start(vp, columns);
	while (i < columns)
		nmat->matrix[i++] = (float)va_arg(vp, double);
	va_end(vp);
	return (nmat);
}

void	ft_mat_del(t_mat **mat)
{
	if (!mat || !*mat)
		return ;
	free((*mat)->matrix);
	free(*mat);
	*mat = NULL;
}
