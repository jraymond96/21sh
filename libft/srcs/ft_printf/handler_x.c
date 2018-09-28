/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:10:30 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:40:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_types.h"

char	*handler_x(va_list lst, t_printf_params params)
{
	char				*str;
	unsigned long long	n;

	n = proper_cast_u(lst, params);
	if (params.precision_spec && params.precision == 0 && n == 0)
		str = ft_strnew(0);
	else
		str = ft_ulltoa_cbase(n, FT_HEX);
	if (params.flags[HASH_FLAG] && n != 0)
		params.width -= 2;
	str = pad_zeroes(str, &params);
	if (params.flags[HASH_FLAG] && n != 0)
	{
		str = ft_strjoin_clr("0x", str, 1);
		params.width += 2;
	}
	return (perform_width(str, &params));
}

char	*handler_x_m(va_list lst, t_printf_params params)
{
	char				*str;
	unsigned long long	n;

	n = proper_cast_u(lst, params);
	if (params.precision_spec && params.precision == 0 && n == 0)
		str = ft_strnew(0);
	else
		str = ft_ulltoa_cbase(n, FT_HEXM);
	if (params.flags[HASH_FLAG] && n != 0)
		params.width -= 2;
	str = pad_zeroes(str, &params);
	if (params.flags[HASH_FLAG] && n != 0)
	{
		str = ft_strjoin_clr("0X", str, 1);
		params.width += 2;
	}
	return (perform_width(str, &params));
}
