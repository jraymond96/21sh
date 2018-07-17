/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 22:53:37 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:37:49 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_types.h"

static char	*handler_flag(char *s, long double n, int l, t_printf_params params)
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
	s = perform_width(s, &params);
	if (adder && adder != '-')
		++params.width;
	if (adder && ((n < 0 && params.precision >= l) || n >= 0))
		s = ft_strjoincs_clr(adder, s);
	if (params.flags[ZERO_FLAG] && adder)
	{
		*ft_strchr(s, adder) = '0';
		s[0] = adder;
	}
	return (s);
}

char		*handler_f(va_list lst, t_printf_params params)
{
	long double	n;
	int			len;
	char		*str;

	n = proper_cast_f(lst, params);
	if (!params.precision_spec
			|| (params.precision_spec && params.precision < 0))
		params.precision = 6;
	str = ft_ldtoa(n, params.precision);
	len = ft_strlen(str);
	if (n < 0 && len <= params.precision)
		str[0] = '0';
	return (handler_flag(str, n, len, params));
}
