/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 21:10:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:04:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"

float	*ft_mat_get(const t_mat *mat, size_t x, size_t y)
{
	if (!mat || !mat->matrix)
		return ((void *)0);
	while (x >= mat->columns)
		x -= mat->columns;
	while (y >= mat->rows)
		y -= mat->rows;
	return (mat->matrix + (x + mat->columns * y));
}
