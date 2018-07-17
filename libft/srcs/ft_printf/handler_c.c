/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 22:30:13 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:35:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"

char	*handler_c(va_list lst, t_printf_params params)
{
	char	*str;
	char	c;

	if (params.flags[L_MOD])
		return (handler_c_m(lst, params));
	c = (char)va_arg(lst, int);
	str = ft_strnew(1);
	str[0] = (c == 0 ? -1 : c);
	return (perform_width(str, &params));
}

char	*handler_c_m(va_list lst, t_printf_params params)
{
	char	*str;
	wchar_t	c;

	c = (wchar_t)va_arg(lst, wchar_t);
	if (c == 0)
	{
		str = ft_strnew(1);
		str[0] = -1;
	}
	else
	{
		if (!(str = ft_getwchar(c)))
			return (NULL);
	}
	return (perform_width(str, &params));
}
