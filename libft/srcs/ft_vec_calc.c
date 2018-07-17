/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:56:07 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 17:07:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec	*ft_vec_calc(t_vec a, t_vec b, t_vec *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_vec_sub(a, b, res));
	else if (op == OP_MULT)
		return (ft_vec_mult(a, b, res));
	else if (op == OP_DIV)
		return (ft_vec_div(a, b, res));
	return (ft_vec_add(a, b, res));
}

t_vec	*ft_vec_calci(t_vec a, float b, t_vec *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_vec_subi(a, b, res));
	else if (op == OP_MULT)
		return (ft_vec_multi(a, b, res));
	else if (op == OP_DIV)
		return (ft_vec_divi(a, b, res));
	return (ft_vec_addi(a, b, res));
}

t_vec	*ft_vec_icalc(float a, t_vec b, t_vec *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_vec_isub(a, b, res));
	else if (op == OP_MULT)
		return (ft_vec_imult(a, b, res));
	else if (op == OP_DIV)
		return (ft_vec_idiv(a, b, res));
	return (ft_vec_iadd(a, b, res));
}
