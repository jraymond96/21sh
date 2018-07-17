/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:00:28 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:15:20 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATRIX_H
# define FT_MATRIX_H

# include "ft_math.h"

typedef struct		s_mat
{
	float			*matrix;
	size_t			rows;
	size_t			columns;
}					t_mat;

t_mat				*ft_mat_new(size_t rows, size_t columns);
t_mat				*ft_mat_newf(size_t rows, size_t columns, float *matrix);
t_mat				*ft_mat_newi(size_t rows, size_t columns, float scalar);
t_mat				*ft_mat_newn(size_t rows, size_t columns, ...);
t_mat				*ft_mat_zero(t_mat *mat);
t_mat				*ft_mat_copy(t_mat *dst, t_mat *src);
t_mat				*ft_mat_dup(t_mat *src);
void				ft_mat_del(t_mat **mat);

void				ft_mat_dump(const t_mat *mat);

t_mat				*ft_mat_opget(size_t rows, size_t cols, t_mat *res);

float				*ft_mat_get(const t_mat *mat, size_t x, size_t y);

/*
** MATRIX ARITHMETICS
*/

t_mat				*ft_mat_add(t_mat a, t_mat b, t_mat *res);
t_mat				*ft_mat_addi(t_mat a, float b, t_mat *res);
t_mat				*ft_mat_iadd(float a, t_mat b, t_mat *res);

t_mat				*ft_mat_sub(t_mat a, t_mat b, t_mat *res);
t_mat				*ft_mat_subi(t_mat a, float b, t_mat *res);
t_mat				*ft_mat_isub(float a, t_mat b, t_mat *res);

t_mat				*ft_mat_mult(t_mat a, t_mat b, t_mat *res);
t_mat				*ft_mat_multi(t_mat a, float b, t_mat *res);
t_mat				*ft_mat_imult(float a, t_mat b, t_mat *res);
t_vec				*ft_mat_multv(t_mat a, t_vec b, t_vec *res);
t_vec				*ft_mat_vmult(t_vec a, t_mat b, t_vec *res);

t_mat				*ft_mat_div(t_mat a, t_mat b, t_mat *res);
t_mat				*ft_mat_divi(t_mat a, float b, t_mat *res);
t_mat				*ft_mat_idiv(float a, t_mat b, t_mat *res);

t_mat				*ft_mat_calc(t_mat a, t_mat b, t_mat *res, t_calcmode op);
t_mat				*ft_mat_calci(t_mat a, float b, t_mat *res, t_calcmode op);
t_mat				*ft_mat_icalc(float a, t_mat b, t_mat *res, t_calcmode op);

/*
** MATRIX TRANSFORMATIONS
*/

t_mat				*ft_mat_rotatex(float angle);
t_mat				*ft_mat_rotatey(float angle);
t_mat				*ft_mat_rotatez(float angle);
t_mat				*ft_mat_rotate(t_vec eulerangles);

t_mat				*ft_mat_scale(t_vec scale);

t_mat				*ft_mat_translate(t_vec translate);

t_mat				*ft_mat_perspective(float fovy, float aspect, float near,
									float far);

t_mat				*ft_mat_lookat(t_vec eye, t_vec center, t_vec up);

#endif
