/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 17:01:04 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/04 16:46:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include <stdarg.h>
# include "ft_printf.h"
# include "ft_printf_ext.h"

void				ft_init_formats(void);
void				ft_init_params(t_printf_params *params, const char *cur_buf,
								const char **format, t_pcur *ap);
char				*ft_handle_format(va_list lst,
								const char **format,
								t_printf_params params);
char				*ft_printf_parser(const char **format, const char *cur_buf,
									t_pcur *ap);

int					check_dollar(const char **index, int n, t_pcur *ap);
int					check_query(const char **index, t_printf_params *params,
							t_pcur *ap);
char				*perform_width(char *str, t_printf_params *params);
char				*pad_zeroes(char *str, t_printf_params *params);
long long			proper_cast(va_list lst, t_printf_params params);
unsigned long long	proper_cast_u(va_list lst, t_printf_params params);
long double			proper_cast_f(va_list lst, t_printf_params params);

char				*handler_s(va_list lst, t_printf_params params);
char				*handler_s_m(va_list lst, t_printf_params params);
char				*handler_d(va_list lst, t_printf_params params);
char				*handler_d_m(va_list lst, t_printf_params params);
char				*handler_u(va_list lst, t_printf_params params);
char				*handler_u_m(va_list lst, t_printf_params params);
char				*handler_p(va_list lst, t_printf_params params);
char				*handler_x(va_list lst, t_printf_params params);
char				*handler_x_m(va_list lst, t_printf_params params);
char				*handler_o(va_list lst, t_printf_params params);
char				*handler_o_m(va_list lst, t_printf_params params);
char				*handler_c(va_list lst, t_printf_params params);
char				*handler_c_m(va_list lst, t_printf_params params);
char				*handler_f(va_list lst, t_printf_params params);
char				*handler_b(va_list lst, t_printf_params params);
char				*handler_y(va_list lst, t_printf_params params);
char				*handler_color(va_list lst, t_printf_params params);
char				*handler_n(va_list lst, t_printf_params params);
char				*handler_r(va_list lst, t_printf_params params);

#endif
