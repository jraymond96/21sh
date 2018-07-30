/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ext.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 20:16:19 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/24 15:40:49 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_EXT_H
# define FT_PRINTF_EXT_H

# include <stdarg.h>
# include "ft_printf.h"

enum
{
	PLUS_FLAG, MINUS_FLAG, HASH_FLAG, ZERO_FLAG, SPACE_FLAG,
	L_MOD, LM_MOD, LL_MOD, H_MOD, HH_MOD, J_MOD, T_MOD, Z_MOD,
	QUERY_FLAG, FLAGS_SIZE
};

typedef struct		s_color_attr
{
	char			*name;
	char			*bg_cd;
	char			*fg_cd;
}					t_color_attr;

typedef struct		s_printf_params
{
	const char		**format;
	const char		*current_buffer;
	t_pcur			*pcur;
	int				width;
	int				precision;
	int				precision_spec;
	int				flags[FLAGS_SIZE];
}					t_printf_params;

typedef char	*(*t_printfunc)(va_list lst, t_printf_params params);

typedef struct		s_printf_format
{
	char			*format;
	t_printfunc		printfunc;
}					t_printf_format;

int					ft_printf_add_format(const char *f, t_printfunc func);
void				ft_printf_free_formats();

#endif
