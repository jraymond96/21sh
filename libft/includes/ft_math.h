/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:41:25 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:12:36 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <string.h>

# define VX vector[0]
# define VY vector[1]
# define VZ vector[2]
# define VW vector[3]

typedef struct		s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_vec3f
{
	float			x;
	float			y;
	float			z;
}					t_vec3f;

typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;

typedef struct		s_vec
{
	float			*vector;
	size_t			dimensions;
}					t_vec;

typedef enum		e_calcmode
{
	OP_ADD, OP_SUB, OP_MULT, OP_DIV
}					t_calcmode;

void				ft_hextorgba(int color, unsigned char rgba[4]);
void				ft_hextorgb(int color, unsigned char rgb[3]);

int					ft_abs(int n);
float				ft_fabs(float n);

int					ft_pow(int x, int y);
long long			ft_powl(long long x, long long y);
double				ft_dpow(double x, int y);
int					ft_sqrt(int n);

int					ft_max(int a, int b);
int					ft_min(int a, int b);

float				ft_fmax(float a, float b);
float				ft_fmin(float a, float b);

unsigned int		ft_umax(unsigned int a, unsigned int b);
unsigned int		ft_umin(unsigned int a, unsigned int b);

t_vec				*ft_vec_new(size_t dimensions);
t_vec				*ft_vec_newf(size_t dimensions, float *vector);
t_vec				*ft_vec_newi(size_t dimensions, float scalar);
t_vec				*ft_vec_newn(size_t dimensions, ...);
t_vec				*ft_vec_zero(t_vec *vec);
t_vec				*ft_vec_copy(t_vec *dst, t_vec *src);
t_vec				*ft_vec_dup(t_vec *src);
void				ft_vec_del(t_vec **vec);

t_vec				*ft_vec_cross(t_vec a, t_vec b, t_vec *res);
float				ft_vec_dot(t_vec *a, t_vec *b);

t_vec				*ft_vec_normalize(t_vec a, t_vec *res);
float				ft_vec_length(t_vec *vec);
float				ft_vec_lengthb(t_vec *vec);

void				ft_vec_dump(const t_vec *vec);
void				ft_vec_dumpn(const t_vec *vec, int precision);

t_vec				*ft_vec_opget(size_t dimensions, t_vec *res);

float				*ft_vec_get(const t_vec *vec, size_t x);

t_vec				*ft_vec_add(t_vec a, t_vec b, t_vec *res);
t_vec				*ft_vec_addi(t_vec a, float b, t_vec *res);
t_vec				*ft_vec_iadd(float a, t_vec b, t_vec *res);

t_vec				*ft_vec_sub(t_vec a, t_vec b, t_vec *res);
t_vec				*ft_vec_subi(t_vec a, float b, t_vec *res);
t_vec				*ft_vec_isub(float a, t_vec b, t_vec *res);

t_vec				*ft_vec_mult(t_vec a, t_vec b, t_vec *res);
t_vec				*ft_vec_multi(t_vec a, float b, t_vec *res);
t_vec				*ft_vec_imult(float a, t_vec b, t_vec *res);

t_vec				*ft_vec_div(t_vec a, t_vec b, t_vec *res);
t_vec				*ft_vec_divi(t_vec a, float b, t_vec *res);
t_vec				*ft_vec_idiv(float a, t_vec b, t_vec *res);

t_vec				*ft_vec_calc(t_vec a, t_vec b, t_vec *res, t_calcmode op);
t_vec				*ft_vec_calci(t_vec a, float b, t_vec *res, t_calcmode op);
t_vec				*ft_vec_icalc(float a, t_vec b, t_vec *res, t_calcmode op);

#endif
