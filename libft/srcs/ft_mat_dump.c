/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:00:05 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:04:10 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include "ft_types.h"
#include "ft_printf.h"
#include <stdlib.h>

int		*get_maxs(const t_mat *mat)
{
	int		*maxs;
	size_t	x;
	size_t	y;

	if (!(maxs = (int *)malloc(sizeof(int) * mat->columns)))
		return (NULL);
	x = 0;
	while (x < mat->columns)
	{
		maxs[x] = 0;
		y = 0;
		while (y < mat->rows)
		{
			maxs[x] = ft_max(maxs[x], ft_intlen(*ft_mat_get(mat, x, y)));
			++y;
		}
		++x;
	}
	return (maxs);
}

void	ft_mat_dump(const t_mat *mat)
{
	size_t	x;
	size_t	y;
	int		*maxs;

	if (!mat)
		return ;
	maxs = get_maxs(mat);
	y = 0;
	while (y < mat->rows)
	{
		x = 0;
		ft_printf("[");
		while (x < mat->columns)
		{
			ft_printf("%*f%s", (maxs ? maxs[x] : 0), *ft_mat_get(mat, x, y),
				(x + 1 < mat->columns ? ", " : "]"));
			if (x + 1 == mat->columns && y + 1 < mat->rows)
				ft_printf("\n");
			++x;
		}
		++y;
	}
	free(maxs);
}
