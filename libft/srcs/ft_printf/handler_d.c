/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:18:02 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:37:14 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_types.h"

static char	*handler_flag(char *s, long long n, int l, t_printf_params params)
{
	char	adder;

	adder = 0;
	if (n < 0)
		adder = '-';
	else if (params.flags[PLUS_FLAG] && n >= 0)
		adder = '+';
	else if (params.flags[SPACE_FLAG] && n >= 0)
		adder = ' ';
	if (adder && adder != '-')
		--params.width;
	s = pad_zeroes(s, &params);
	if (adder && adder != '-')
		++params.width;
	if (adder && ((n < 0 && params.precision >= l) || n >= 0))
		s = ft_strjoincs_clr(adder, s);
	s = perform_width(s, &params);
	if (params.flags[ZERO_FLAG] && adder)
	{
		*ft_strchr(s, adder) = '0';
		s[0] = adder;
	}
	return (s);
}

char		*handler_d(va_list lst, t_printf_params params)
{
	long long	n;
	int			len;
	char		*str;

	n = proper_cast(lst, params);
	if (params.precision_spec && params.precision == 0 && n == 0)
		str = ft_strnew(0);
	else
		str = ft_lltoa(n);
	len = ft_strlen(str);
	if (n < 0 && len <= params.precision)
		str[0] = '0';
	return (handler_flag(str, n, len, params));
}

char		*handler_d_m(va_list lst, t_printf_params params)
{
	params.flags[LL_MOD] = 0;
	params.flags[L_MOD] = 1;
	return (handler_d(lst, params));
}
