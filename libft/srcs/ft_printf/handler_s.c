/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:56:04 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/26 14:23:03 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_math.h"
#include "ft_mem.h"

char		*handler_s(va_list lst, t_printf_params params)
{
	char	*gs;
	int		slen;

	if (params.flags[L_MOD])
		return (handler_s_m(lst, params));
	gs = (char *)va_arg(lst, char *);
	if (!gs)
		gs = (params.flags[J_MOD] ? "" : "(null)");
	if (params.precision_spec && params.precision == 0)
		return (ft_strnew(0));
	slen = ft_strlen(gs);
	if (params.precision_spec && params.precision < slen
			&& params.precision >= 0)
		slen = params.precision;
	gs = ft_strndup(gs, slen);
	return (perform_width(gs, &params));
}

static char	*get_proper_gs(wchar_t *ws, t_printf_params *params)
{
	if (ws && params->precision_spec)
	{
		params->precision = ft_wstrnlen(ws, params->precision);
		return (ft_getnwstr(ws, params->precision));
	}
	return (ft_getwstr(ws));
}

char		*handler_s_m(va_list lst, t_printf_params params)
{
	wchar_t	*ws;
	char	*gs;
	char	*str;
	char	*ostr;
	int		slen;

	ws = (wchar_t *)va_arg(lst, wchar_t *);
	if (!(gs = get_proper_gs(ws, &params)) && ws)
		return (NULL);
	str = (gs ? gs : "(null)");
	if (!gs && params.flags[J_MOD])
		str = "";
	slen = ft_strlen(str);
	if (params.precision_spec && params.precision < slen)
		slen = params.precision;
	ostr = str;
	str = ft_strndup(ostr, slen);
	if (gs)
		free(ostr);
	return (perform_width(str, &params));
}

char		*handler_r(va_list lst, t_printf_params params)
{
	char	*gs;
	int		i;

	gs = (char *)va_arg(lst, char *);
	if (!gs)
		gs = "(null)";
	params.precision = ft_abs(params.precision);
	gs = (char *)ft_memcpy(ft_memalloc(params.precision + 1),
			(void *)gs, params.precision);
	i = 0;
	while (i < params.precision)
	{
		if (gs[i] == 0)
			gs[i] = -1;
		++i;
	}
	return (perform_width(gs, &params));
}
