/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proper_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 16:48:04 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 22:31:53 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <stdlib.h>
#include "handlers.h"

long long			proper_cast(va_list lst, t_printf_params params)
{
	if (params.flags[J_MOD])
		return ((long long)va_arg(lst, intmax_t));
	else if (params.flags[Z_MOD])
		return ((long long)va_arg(lst, size_t));
	else if (params.flags[LL_MOD])
		return ((long long)va_arg(lst, long long));
	else if (params.flags[L_MOD])
		return ((long long)va_arg(lst, long));
	else if (params.flags[H_MOD])
		return ((long long)((short)va_arg(lst, int)));
	else if (params.flags[HH_MOD])
		return ((long long)((char)va_arg(lst, int)));
	return ((long long)va_arg(lst, int));
}

unsigned long long	proper_cast_u(va_list lst, t_printf_params params)
{
	unsigned int	n;

	if (params.flags[J_MOD])
		return ((unsigned long long)va_arg(lst, intmax_t));
	else if (params.flags[Z_MOD])
		return ((unsigned long long)va_arg(lst, size_t));
	else if (params.flags[LL_MOD])
		return ((unsigned long long)va_arg(lst, unsigned long long));
	else if (params.flags[L_MOD])
		return ((unsigned long long)va_arg(lst, unsigned long));
	else if (params.flags[H_MOD])
		n = (unsigned int)((unsigned short)va_arg(lst, unsigned int));
	else if (params.flags[HH_MOD])
		n = (unsigned int)((unsigned char)va_arg(lst, unsigned int));
	else
		n = (unsigned int)va_arg(lst, unsigned int);
	return ((unsigned long long)n);
}

long double			proper_cast_f(va_list lst, t_printf_params params)
{
	if (params.flags[LM_MOD])
		return ((long double)va_arg(lst, long double));
	return ((long double)va_arg(lst, double));
}
