/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:18:28 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 21:38:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_types.h"
#include "ft_str.h"

char	*handler_p(va_list lst, t_printf_params params)
{
	char	*str;
	void	*ptr;

	ptr = (void *)va_arg(lst, void *);
	if (ptr == 0 && params.precision_spec && params.precision == 0)
		str = ft_strnew(0);
	else
		str = ft_ulltoa_cbase((unsigned long long)ptr, FT_HEX);
	params.width -= 2;
	str = pad_zeroes(str, &params);
	params.width += 2;
	return (perform_width(ft_strjoin_clr("0x", str, 1), &params));
}
