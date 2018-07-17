/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:03:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:00:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

float	*ft_vec_get(const t_vec *a, size_t x)
{
	if (!a)
		return (NULL);
	while (x >= a->dimensions)
		x -= a->dimensions;
	return (a->vector + x);
}
