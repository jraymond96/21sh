/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:59:21 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/25 16:27:32 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"

char	*perform_width(char *str, t_printf_params *params)
{
	char	*s;
	int		len;

	len = params->width - ft_strlen(str);
	s = NULL;
	if (len > 0)
		s = ft_memset(ft_memalloc(len + 1), ' ', len);
	if (params->flags[ZERO_FLAG] && !params->flags[MINUS_FLAG] && s)
		s = ft_memset(s, '0', len);
	if (params->flags[MINUS_FLAG])
		s = ft_strjoin_clr(str, s, 2);
	else
		s = ft_strjoin_clr(s, str, 2);
	return (s);
}

char	*pad_zeroes(char *str, t_printf_params *params)
{
	int		len;
	int		zeroes;
	char	*zstr;

	len = ft_strlen(str);
	zeroes = 0;
	zstr = NULL;
	if (params->precision_spec)
	{
		params->flags[ZERO_FLAG] = 0;
		zeroes = params->precision - len;
	}
	else if (params->flags[ZERO_FLAG] && !params->flags[MINUS_FLAG])
		zeroes = params->width - len;
	if (zeroes > 0)
		zstr = (char *)ft_memset(ft_memalloc(zeroes + 1), '0', zeroes);
	return (ft_strjoin_clr(zstr, str, 2));
}

int		check_dollar(const char **index, int n, t_pcur *ap)
{
	if (**index == '$')
	{
		va_end(ap->ap_cur);
		va_copy(ap->ap_cur, ap->ap);
		while (--n)
			va_arg(ap->ap_cur, int);
		++(*index);
		return (1);
	}
	return (0);
}

int		check_query(const char **index, t_printf_params *params, t_pcur *ap)
{
	if (**index == '?')
	{
		++(*index);
		if (**index == '*')
		{
			++(*index);
			params->flags[QUERY_FLAG] = (int)va_arg(ap->ap_cur, int);
		}
		else
		{
			params->flags[QUERY_FLAG] = ft_atoi(*index);
			while (ft_isdigit(**index))
				++(*index);
		}
		return (1);
	}
	return (0);
}
