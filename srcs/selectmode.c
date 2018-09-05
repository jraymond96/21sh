/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 20:08:48 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/05 23:17:45 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"

#include "../logger/incs/logger.h"

static void	handle_xy_cursor(t_bufferl *bl, int left)
{
	ft_getsize(&bl->h, &bl->w);
	if (left == 1)
	{
		if (bl->cursor-- == 0)
		{
			bl->cursor = 0;
			return ;
		}
		log_trace("x: %d\n", bl->x);
		bl->x = (bl->x == 1) ? bl->w : --bl->x;
		log_trace("x: %d\n", bl->x);
		bl->y = (bl->x == bl->w) ? --bl->y : bl->y;
	}
	else
	{
			bl->cursor++;
			bl->x = (bl->x == bl->w) ? 1 : ++bl->x;
			bl->y = (bl->x == 1) ? ++bl->y : bl->y;
	}
}

static void	reprint_line2(t_bufferl *bl, int i)
{
	int	y;

	y = bl->y;
	ft_getsize(&bl->h, &bl->w);
	ft_printf("\033[s\033[%d;%dH\033[K", bl->y, bl->x);
	while (++y <= bl->h)
		ft_printf("\033[%dF\033[2K", y);
	ft_printf("\033[u%{white}%.*s%{0}", i, (bl->line + bl->cursor));
	while (i--)
		handle_xy_cursor(bl, 0);
	ft_printf("%s", (bl->line + bl->cursor));
}

int			selectmode(t_bufferl *bl, int c)
{
	static char	buff[500];
	int			i;
	int			d;

	d = 0;
	i = 1;
	*buff = '\0';
	if (c == 'R')
	{
		log_debug("start selectmode: '%c'\n", bl->line[bl->cursor - 1]);
		if (!bl->line[bl->cursor])
		{
			ft_printf("\033[D");
			handle_xy_cursor(bl, 1);
		}
		while (1)
		{
			if ((d == 27 || (d = ft_getch()) == 27) &&
					(d = ft_getch()) == 91 && (d = ft_getch()))
			{
				if (d == 'C')
				{
					log_trace("BFORE: x: %d y:%d\n", bl->x, bl->y);
					handle_xy_cursor(bl, 0);
					log_trace("AFTER: x: %d y:%d\n", bl->x, bl->y);
					i++;
					reprint_line2(bl, i);
				}
				else if (d == 'D')
				{
					log_trace("BFORE: x: %d y:%d\n", bl->x, bl->y);
					handle_xy_cursor(bl, 1);
					log_trace("AFTER: x: %d y:%d\n", bl->x, bl->y);
					i++;
					reprint_line2(bl, i);
				}
				else if (d == '1' && (d = ft_getch()) == ';' && (d = ft_getch()) == '2'
							&& ((d = ft_getch()) == 'R' || d == 'S'))
				{
					log_debug("enddddddd selectmode\n");
					break;
				}
			}
		}
	}
	return (0);
}
