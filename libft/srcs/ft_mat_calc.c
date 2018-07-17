/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:50:53 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 18:03:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_matrix.h"

t_mat	*ft_mat_calc(t_mat a, t_mat b, t_mat *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_mat_sub(a, b, res));
	else if (op == OP_MULT)
		return (ft_mat_mult(a, b, res));
	else if (op == OP_DIV)
		return (ft_mat_div(a, b, res));
	return (ft_mat_add(a, b, res));
}

t_mat	*ft_mat_calci(t_mat a, float b, t_mat *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_mat_subi(a, b, res));
	else if (op == OP_MULT)
		return (ft_mat_multi(a, b, res));
	else if (op == OP_DIV)
		return (ft_mat_divi(a, b, res));
	return (ft_mat_addi(a, b, res));
}

t_mat	*ft_mat_icalc(float a, t_mat b, t_mat *res, t_calcmode op)
{
	if (op == OP_SUB)
		return (ft_mat_isub(a, b, res));
	else if (op == OP_MULT)
		return (ft_mat_imult(a, b, res));
	else if (op == OP_DIV)
		return (ft_mat_idiv(a, b, res));
	return (ft_mat_iadd(a, b, res));
}
