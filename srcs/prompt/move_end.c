/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 23:14:54 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/14 16:54:43 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"

static void	move_paste(t_bufferl *bl)
{
	static char	line_sm[8192];
	int			i;

	i = 0;
	if (!bl->sm && line_sm[i])
		while (line_sm[i])
			add_char(bl, (int)line_sm[i++]);
	else if (bl->sm)
	{
		ft_strclr(line_sm);
		if (bl->cursor > bl->sm_cursor)
			ft_strncpy(line_sm, bl->line + bl->sm_cursor,
					bl->cursor - bl->sm_cursor + 1);
		else if (bl->sm_cursor > bl->cursor)
			ft_strncpy(line_sm, bl->line + bl->cursor,
					bl->sm_cursor - bl->cursor + 1);
		else
			ft_strncpy(line_sm, bl->line + bl->cursor, 1);
		bl->sm = 0;
		ft_printf("\033[?25h\033[s%{0}\033[%d;%dH%s\033[u", bl->ys, bl->xs,
				bl->line);
	}
}

static void	move_tild(t_bufferl *bl, int c)
{
	if (c == '5')
	{
		if (bl->sm)
			ft_printf("\033[?25h\033[s%{0}\033[%d;%dH%s\033[u", bl->ys, bl->xs,
					bl->line);
		else
		{
			if ((int)bl->cursor == bl->len)
				escape_char(bl, 'D');
			ft_putstr("\033[?25l");
			bl->sm_x = bl->x;
			bl->sm_y = bl->y;
			bl->sm_cursor = bl->cursor;
		}
		bl->sm = !bl->sm;
	}
	else if (c == '6')
		move_paste(bl);
}

void		move_end(t_bufferl *bl, int c)
{
	int	ny;

	if (c == 'H' && bl->cursor != 0)
	{
		bl->cursor = 0;
		bl->x = bl->xs;
		bl->y = bl->ys;
		ft_printf("\033[%d;%dH", bl->y, bl->x);
	}
	else if (c == 'F' && (int)bl->cursor != bl->len)
	{
		ft_getsize(NULL, &bl->w);
		bl->x = (bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x;
		ny = (bl->x - 1) / bl->w;
		bl->y += ny;
		bl->x -= (bl->w * ny);
		bl->cursor = bl->len;
		ft_printf("\033[%d;%dH", bl->y, bl->x);
	}
	else if ((c == '5' || c == '6') && ft_getch() == '~')
		move_tild(bl, c);
}
