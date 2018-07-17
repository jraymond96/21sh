/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_formats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 22:52:10 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/04 16:41:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_mem.h"

static void		ft_init_addon(void)
{
	ft_printf_add_format("f", handler_f);
	ft_printf_add_format("F", handler_f);
	ft_printf_add_format("b", handler_b);
	ft_printf_add_format("y", handler_y);
	ft_printf_add_format("{", handler_color);
	ft_printf_add_format("n", handler_n);
	ft_printf_add_format("r", handler_r);
}

void			ft_init_formats(void)
{
	static int	frst_call = 0;

	if (frst_call == 0)
	{
		frst_call = 1;
		ft_printf_add_format("s", handler_s);
		ft_printf_add_format("S", handler_s_m);
		ft_printf_add_format("p", handler_p);
		ft_printf_add_format("d", handler_d);
		ft_printf_add_format("D", handler_d_m);
		ft_printf_add_format("i", handler_d);
		ft_printf_add_format("o", handler_o);
		ft_printf_add_format("O", handler_o_m);
		ft_printf_add_format("u", handler_u);
		ft_printf_add_format("U", handler_u_m);
		ft_printf_add_format("x", handler_x);
		ft_printf_add_format("X", handler_x_m);
		ft_printf_add_format("c", handler_c);
		ft_printf_add_format("C", handler_c_m);
		ft_init_addon();
	}
}

void			ft_init_params(t_printf_params *params, const char *cur_buf,
							const char **format, t_pcur *ap)
{
	ft_bzero(params, sizeof(t_printf_params));
	params->flags[QUERY_FLAG] = 1;
	params->current_buffer = cur_buf;
	params->format = format;
	params->pcur = ap;
}
