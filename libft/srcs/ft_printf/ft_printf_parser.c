/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:03:19 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/13 19:38:28 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_math.h"
#include "ft_types.h"
#include "ft_str.h"

static int	ft_is_flag(char c, t_printf_params *params)
{
	if (c == '#')
		return (params->flags[HASH_FLAG] = 1);
	else if (c == '+')
		return (params->flags[PLUS_FLAG] = 1);
	else if (c == '-')
		return (params->flags[MINUS_FLAG] = 1);
	else if (c == '0')
		return (params->flags[ZERO_FLAG] = 1);
	else if (c == ' ')
		return (params->flags[SPACE_FLAG] = 1);
	return (0);
}

static int	ft_is_width(const char **index, t_printf_params *params,
					t_pcur *ap)
{
	int	t;

	if (ft_isdigit(**index))
	{
		t = ft_atoi(*index);
		while (ft_isdigit(**index))
			++(*index);
		if (!check_dollar(index, t, ap))
			params->width = t;
		return (1);
	}
	else if (**index == '*')
	{
		if ((params->width = (int)va_arg(ap->ap_cur, int)) < 0)
		{
			params->width = ft_abs(params->width);
			params->flags[MINUS_FLAG] = 1;
		}
		++(*index);
		return (1);
	}
	return (0);
}

static int	ft_is_precision(const char **index, t_printf_params *params,
						t_pcur *ap)
{
	if (**index == '.')
	{
		params->precision_spec = 1;
		if (ft_isdigit(*++(*index)))
		{
			params->precision = ft_atoi(*index);
			while (ft_isdigit(**index))
				++(*index);
		}
		else if (**index == '*')
		{
			if ((params->precision = (int)va_arg(ap->ap_cur, int)) < 0)
				params->precision_spec = 0;
			++(*index);
			return (1);
		}
		else
			params->precision = 0;
		return (1);
	}
	return (0);
}

static int	ft_is_modifier(const char **index, t_printf_params *params)
{
	if (ft_strnequ("ll", *index, 2))
		return (params->flags[LL_MOD] = 2);
	else if (ft_strnequ("hh", *index, 2))
		return (params->flags[HH_MOD] = 2);
	else if (**index == 'l')
		return (params->flags[L_MOD] = 1);
	else if (**index == 'h')
		return (params->flags[H_MOD] = 1);
	else if (**index == 'j')
		return (params->flags[J_MOD] = 1);
	else if (**index == 'z')
		return (params->flags[Z_MOD] = 1);
	else if (**index == 'L')
		return (params->flags[LM_MOD] = 1);
	return (0);
}

char		*ft_printf_parser(const char **format, const char *cur_buf,
						t_pcur *ap)
{
	t_printf_params	params;
	int				inc_format;
	char			*buffer;

	ft_init_params(&params, cur_buf, format, ap);
	while (**format)
	{
		if (ft_is_flag(**format, &params))
			++(*format);
		else if (ft_is_width(format, &params, ap))
			;
		else if (ft_is_precision(format, &params, ap))
			;
		else if (check_query(format, &params, ap))
			;
		else if ((inc_format = ft_is_modifier(format, &params)))
			(*format) += inc_format;
		else
		{
			buffer = ft_handle_format(ap->ap_cur, format, params);
			return (ft_strrepeat_clr(buffer, params.flags[QUERY_FLAG]));
		}
	}
	return (ft_strnew(0));
}
