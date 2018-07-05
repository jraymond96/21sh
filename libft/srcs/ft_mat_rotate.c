/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 21:04:44 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:22:13 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include <math.h>

t_mat	*ft_mat_rotatex(float angle)
{
	float	cangle;
	float	sangle;

	cangle = cosf(angle * M_PI / 180.f);
	sangle = sinf(angle * M_PI / 180.f);
	return (ft_mat_newn(4, 4,
				1.f, 0.f, 0.f, 0.f,
				0.f, cangle, -sangle, 0.f,
				0.f, sangle, cangle, 0.f,
				0.f, 0.f, 0.f, 1.f));
}

t_mat	*ft_mat_rotatey(float angle)
{
	float	cangle;
	float	sangle;

	cangle = cosf(angle * M_PI / 180.f);
	sangle = sinf(angle * M_PI / 180.f);
	return (ft_mat_newn(4, 4,
				cangle, 0.f, sangle, 0.f,
				0.f, 1.f, 0.f, 0.f,
				-sangle, 0.f, cangle, 0.f,
				0.f, 0.f, 0.f, 1.f));
}

t_mat	*ft_mat_rotatez(float angle)
{
	float	cangle;
	float	sangle;

	cangle = cosf(angle * M_PI / 180.f);
	sangle = sinf(angle * M_PI / 180.f);
	return (ft_mat_newn(4, 4,
				cangle, -sangle, 0.f, 0.f,
				sangle, cangle, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f));
}

t_mat	*ft_mat_rotate(t_vec eulerangles)
{
	t_mat	*res;
	t_mat	*rotx;
	t_mat	*roty;
	t_mat	*rotz;

	if (!eulerangles.vector || eulerangles.dimensions < 3)
		return (NULL);
	rotx = ft_mat_rotatex(eulerangles.vector[0]);
	roty = ft_mat_rotatey(eulerangles.vector[1]);
	rotz = ft_mat_rotatez(eulerangles.vector[2]);
	res = ft_mat_mult(*rotz, *roty, NULL);
	ft_mat_mult(*res, *rotx, res);
	ft_mat_del(&rotx);
	ft_mat_del(&roty);
	ft_mat_del(&rotz);
	return (res);
}
