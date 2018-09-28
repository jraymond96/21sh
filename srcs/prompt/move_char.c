/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:26:05 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/09 21:55:00 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"

static void	reprint_line(t_bufferl *bl)
{
	int		ny;
	int		ny2;
	int		ny3;
	char	halfc[8192];

	ft_getsize(&bl->h, &bl->w);
	ny = (bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x;
	ny2 = (ny - 1) / bl->w;
	ny3 = ny - (bl->w * ny2);
	ft_strcpy(halfc, bl->line + (bl->cursor - 1));
	ft_strrepc_str(halfc, "\t\n", " ~");
	if (bl->y + ny2 > bl->h && ny3 == 1)
	{
		--bl->ys;
		--bl->y;
		ft_printf("\033[s%s\033[u\033[A\033[C", halfc);
	}
	else
		ft_printf("\033[s%s\033[u\033[C", halfc);
}

void		delete_char(t_bufferl *bl)
{
	int		x;
	char	halfc[8192];

	if (bl->cursor)
	{
		ft_strerase(bl->line, --bl->cursor, 1);
		--bl->len;
		ft_getsize(&bl->h, &x);
		if (--bl->x <= 0)
		{
			--bl->y;
			ft_printf("\033[A\033[%dC", (bl->x = x));
		}
		else
			ft_putstr("\033[D");
		ft_strrepc_str(ft_strcpy(halfc, bl->line + bl->cursor), "\t\n", " ~");
		ft_printf("\033[s%s\033[K", halfc);
		if (bl->y < bl->h)
			ft_printf("\033[B\r\033[K\033[u%s", halfc);
		ft_putstr("\033[u");
	}
}

void		add_char(t_bufferl *bl, int c)
{
	if (bl->len + 1 == (int)bl->size)
		return ;
	ft_getsize(&bl->h, &bl->w);
	ft_strinsert(bl->line, (char *)&c, bl->cursor++, 1);
	bl->line[++bl->len] = '\0';
	reprint_line(bl);
	if (++bl->x > bl->w)
	{
		bl->x = 1;
		if (++bl->y > bl->h)
		{
			--bl->ys;
			--bl->y;
		}
		ft_putstr("\n");
	}
}

void		reprint_sm(t_bufferl *bl)
{
	if (bl->cursor > bl->sm_cursor)
	{
		if ((int)bl->cursor == bl->len)
			escape_char(bl, 'D');
		ft_printf("\033[s%{0}\033[%d;%dH%.*s", bl->ys, bl->xs, bl->sm_cursor,
				bl->line);
		ft_printf("%#{white}%{black}%.*s", bl->cursor - bl->sm_cursor + 1,
				bl->line + bl->sm_cursor);
		ft_printf("%{0}%s\033[u", bl->line + bl->cursor + 1);
	}
	else if (bl->sm_cursor >= bl->cursor)
	{
		ft_printf("\033[s%{0}\033[%d;%dH%.*s", bl->ys, bl->xs, bl->cursor,
				bl->line);
		ft_printf("%#{white}%{black}%.*s",
			bl->sm_cursor - bl->cursor + 1, bl->line + bl->cursor);
		ft_printf("%{0}%s\033[u", bl->line + bl->sm_cursor + 1);
	}
}
