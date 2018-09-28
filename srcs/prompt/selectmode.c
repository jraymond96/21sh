/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selectmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 20:08:48 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/25 16:21:16 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"

static void	copy(char *buff, t_bufferl *bl, t_slctmode *sm)
{
	ft_strclr(buff);
	if (sm->save_cur > (int)bl->cursor)
		ft_strncpy(buff, (bl->line + bl->cursor),
				(sm->save_cur - bl->cursor + 1));
	else
		ft_strncpy(buff, (bl->line + sm->save_cur),
				(bl->cursor - sm->save_cur + 1));
}

static void	initsm(t_slctmode *sm, t_bufferl *bl)
{
	sm->save_x = bl->x;
	sm->save_y = bl->y;
	sm->save_cur = bl->cursor;
}

static int	call_getch(short opt, int *c)
{
	if (opt)
	{
		if (!(*c == 27 || (*c = ft_getch()) == 27))
			return (-1);
		if (!((*c = ft_getch()) == 91))
			return (-1);
		*c = ft_getch();
	}
	else
	{
		if (!((*c == '1' && (*c = ft_getch()) == ';')))
			return (-1);
		if (!((*c = ft_getch()) == '2'))
			return (-1);
		if (!((*c = ft_getch()) == 'R' || *c == 'S'))
			return (-1);
	}
	return (0);
}

static void	loop(t_bufferl *bl, t_slctmode *sm, int *c, char *buff)
{
	while (1)
	{
		if (call_getch(1, c) != -1)
		{
			if (*c == 'C')
			{
				ft_printf("\033[s\033[%d;%dH%s\033[u",
							bl->ys, bl->xs, bl->line);
				handle_xy_cursor(bl, 0);
				reprint_line3(bl, sm);
			}
			else if (*c == 'D')
			{
				handle_xy_cursor(bl, 1);
				reprint_line3(bl, sm);
			}
			else if (call_getch(0, c) != -1)
			{
				if (*c == 'S')
					copy(buff, bl, sm);
				ft_printf("\033[%d;%dH", bl->y, bl->x);
				break ;
			}
		}
	}
}

int			selectmode(t_bufferl *bl, int c)
{
	t_slctmode	sm;
	static char	buff[500];
	int			i;

	if (!bl->cursor)
		return (0);
	if (c == 'R')
	{
		c = 0;
		if (!bl->line[bl->cursor])
		{
			ft_printf("\033[D");
			handle_xy_cursor(bl, 1);
		}
		initsm(&sm, bl);
		loop(bl, &sm, &c, buff);
		ft_printf("\033[s\033[%d;%dH%s\033[u", bl->ys, bl->xs, bl->line);
	}
	else if (c == 'S')
	{
		i = -1;
		while (buff[++i])
			add_char(bl, (int)buff[i]);
	}
	return (0);
}
