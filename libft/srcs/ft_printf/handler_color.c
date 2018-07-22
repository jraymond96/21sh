/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 22:49:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/18 21:44:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handlers.h"
#include "ft_str.h"
#include "ft_printf.h"
#include "ft_types.h"
#include "ft_math.h"

static const t_color_attr	g_colors[] = {
	{"black", "\e[30m", "\e[40m"}, {"red", "\e[31m", "\e[41m"},
	{"green", "\e[32m", "\e[42m"}, {"yellow", "\e[33m", "\e[43m"},
	{"blue", "\e[34m", "\e[44m"}, {"magenta", "\e[35m", "\e[45m"},
	{"cyan", "\e[36m", "\e[46m"}, {"lgrey", "\e[37m", "\e[47m"},
	{"dgrey", "\e[90m", "\e[100m"}, {"lred", "\e[91m", "\e[101m"},
	{"lgreen", "\e[92m", "\e[102m"}, {"lyellow", "\e[93m", "\e[103m"},
	{"lblue", "\e[94m", "\e[104m"}, {"lmagenta", "\e[95m", "\e[105m"},
	{"lcyan", "\e[96m", "\e[106m"}, {"white", "\e[97m", "\e[107m"},
	{"bold", "\e[1m", "\e[1m"}, {"dim", "\e[2m", "\e[2m"},
	{"italic", "\e[3m", "\e[3m"}, {"underlined", "\e[4m", "\e[4m"},
	{"invert", "\e[7m", "\e[7m"}, {"hide", "\e[8m", "\e[8m"},
	{"eoc", "\e[0m", "\e[0m"}, {"0", "\e[0m", "\e[0m"}
};
static const size_t		g_colors_n = (sizeof(g_colors) / sizeof(t_color_attr));

static char			*get_color(char *tcolor, int fb)
{
	static char		*str;
	size_t			i;
	unsigned char	rgb[3];

	i = 0;
	if (ft_strnequ(tcolor, "0x", 2) || ft_strnequ(tcolor, "0X", 2))
	{
		ft_hextorgb(ft_atoi_basec(tcolor + 2, FT_HEX), rgb);
		ft_printf_s(&str, "\e[%s;2;%hhu;%hhu;%hhum", (fb ? "48" : "38"),
				rgb[0], rgb[1], rgb[2]);
		return (str);
	}
	while (i < g_colors_n)
	{
		if (ft_strequ(g_colors[i].name, tcolor))
			return (fb ? g_colors[i].fg_cd : g_colors[i].bg_cd);
		++i;
	}
	return ("");
}

static char			*all_colors(char *tcolor, char esc_fb[12],
							t_printf_params params)
{
	char	*final;
	char	*total;
	int		pos;

	pos = 0;
	total = NULL;
	while (pos != -1)
	{
		if ((pos = ft_strchr_pos(tcolor, '/')) != -1)
			tcolor[pos] = '\0';
		if (params.precision > 0)
			final = ft_strjoin_clr(esc_fb, ft_strjoinc(tcolor, 'm'), 1);
		else if (tcolor[0] == ';')
			final = ft_strjoin_clr(esc_fb, ft_strjoinc(tcolor + 1, 'm'), 1);
		else
			final = ft_strdup(get_color(tcolor, params.width));
		if (pos != -1)
			tcolor += pos + 1;
		total = ft_strjoin_clr(total, final, 2);
	}
	return (total);
}

static char			*perform_color(char *tcolor, t_printf_params params)
{
	char	esc_fb[12];
	char	*total;

	if (params.flags[MINUS_FLAG])
	{
		free(tcolor);
		return (ft_strdup("\e[0m"));
	}
	ft_strcpy(esc_fb, "\e[38;2;");
	if (params.width > 0)
		ft_strncpy(esc_fb + 2, "48", 2);
	total = all_colors(tcolor, esc_fb, params);
	free(tcolor);
	return (total);
}

char				*handler_color(va_list lst, t_printf_params params)
{
	char	*color;
	char	*tcolor;
	int		pos;

	(void)lst;
	if ((pos = ft_strchr_pos(*params.format, '}')) == -1)
		return (ft_strdup("{"));
	if (params.flags[HASH_FLAG])
		params.width = 1;
	if (params.flags[L_MOD])
		params.precision = 1;
	if (!(color = ft_strndup(*params.format, pos)))
		return (NULL);
	*params.format += pos + 1;
	tcolor = ft_inner_printf(color, params.pcur).buf;
	free(color);
	if (tcolor[0] == '-')
	{
		free(tcolor);
		return (ft_strnew(0));
	}
	return (perform_color(ft_strtrim_clr(tcolor), params));
}
