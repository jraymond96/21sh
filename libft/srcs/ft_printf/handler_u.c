/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:18:17 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:40:02 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_types.h"
#include "ft_str.h"

char	*handler_u(va_list lst, t_printf_params params)
{
	unsigned long long	n;
	char				*str;

	n = proper_cast_u(lst, params);
	if (params.precision_spec && params.precision == 0 && n == 0)
		str = ft_strnew(0);
	else
		str = ft_ulltoa(n);
	return (perform_width(pad_zeroes(str, &params), &params));
}

char	*handler_u_m(va_list lst, t_printf_params params)
{
	params.flags[LL_MOD] = 0;
	params.flags[L_MOD] = 1;
	return (handler_u(lst, params));
}
