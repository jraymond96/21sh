/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:48:07 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/19 17:58:56 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_types.h"

char	*handler_b(va_list lst, t_printf_params params)
{
	char	*str;

	str = ft_ulltoa_cbase(proper_cast_u(lst, params), FT_BIN);
	return (perform_width(pad_zeroes(str, &params), &params));
}

char	*handler_n(va_list lst, t_printf_params params)
{
	int	*n;

	if ((n = (int *)va_arg(lst, int *)))
		*n = ft_strlen(params.current_buffer);
	return (ft_strnew(0));
}
