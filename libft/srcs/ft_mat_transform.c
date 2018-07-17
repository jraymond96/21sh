/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:22:33 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:52:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"
#include <math.h>

t_mat	*ft_mat_scale(t_vec scale)
{
	if (!scale.vector || scale.dimensions < 3)
		return (NULL);
	return (ft_mat_newn(4, 4,
				scale.vector[0], 0.f, 0.f, 0.f,
				0.f, scale.vector[1], 0.f, 0.f,
				0.f, 0.f, scale.vector[2], 0.f,
				0.f, 0.f, 0.f, 1.f));
}

t_mat	*ft_mat_translate(t_vec translate)
{
	if (!translate.vector || translate.dimensions < 3)
		return (NULL);
	return (ft_mat_newn(4, 4,
				1.f, 0.f, 0.f, translate.vector[0],
				0.f, 1.f, 0.f, translate.vector[1],
				0.f, 0.f, 1.f, translate.vector[2],
				0.f, 0.f, 0.f, 1.f));
}

t_mat	*ft_mat_perspective(float fovy, float aspect, float near, float far)
{
	float	tfovy;

	tfovy = tan((fovy) / 2.f);
	return (ft_mat_newn(4, 4,
				1.f / (aspect * tfovy), 0.f, 0.f, 0.f,
				0.f, 1.f / tfovy, 0.f, 0.f, 0.f,
				0.f, 0.f, -(far + near) / (far - near), -1.f,
				0.f, 0.f, -(2.f * far * near) / (far - near), 0.f));
}

t_mat	*ft_mat_lookat(t_vec eye, t_vec center, t_vec up)
{
	t_vec	*f;
	t_vec	*s;
	t_vec	*u;
	t_mat	*mat;

	f = ft_vec_sub(center, eye, NULL);
	ft_vec_normalize(*f, f);
	s = ft_vec_cross(*f, up, NULL);
	ft_vec_normalize(*s, s);
	u = ft_vec_cross(*s, *f, NULL);
	mat = ft_mat_newn(4, 4,
			s->vector[0], u->vector[0], -f->vector[0], 1.0f,
			s->vector[1], u->vector[1], -f->vector[1], 1.0f,
			s->vector[2], u->vector[2], -f->vector[2], 1.0f,
			-ft_vec_dot(s, &eye), -ft_vec_dot(u, &eye), ft_vec_dot(f, &eye));
	ft_vec_del(&f);
	ft_vec_del(&s);
	ft_vec_del(&u);
	return (mat);
}
