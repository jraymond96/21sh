/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 21:52:48 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/09 23:40:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"

static void	move_d(t_bufferl *bl)
{
	int	pos;
	int	i;
	int	bx;

	i = bl->cursor - 1;
	pos = -1;
	if (bl->cursor > 0)
		while ((pos = ft_strnrpbrk_pos(bl->line, " \t", i)) == i)
			--i;
	pos = (pos == -1 ? 0 : pos + 1);
	ft_putchar('\r');
	bx = bl->x;
	if ((bl->x -= bl->cursor - pos) <= 0)
	{
		bl->cursor -= bx - 1;
		bl->x = 1;
	}
	else
	{
		bl->cursor = pos;
		if (bl->x - 1)
			ft_printf("\r\033[%dC", bl->x - 1);
	}
}

static void	move_c(t_bufferl *bl)
{
	int	pos;
	int	bx;
	int	i;

	ft_getsize(NULL, &bl->w);
	i = 1;
	while ((pos = ft_strpbrk_pos(bl->line + bl->cursor + i, " \t")) == 0)
		++i;
	if (pos == -1)
		pos = bl->len - 1;
	else
		pos += (bl->cursor ? (int)bl->cursor + (i - 1) : 0);
	bx = bl->x;
	if ((bl->x += pos - bl->cursor) > bl->w)
	{
		bl->cursor += bl->w - bx;
		if (bl->w - bx)
			ft_printf("\033[%dC", bl->w - bx);
		bl->x = bl->w;
	}
	else
		ft_printf("\r\033[%dC", bl->x - 1, (bl->cursor = pos));
}

static void	move_b(t_bufferl *bl)
{
	int	i;
	int	bx;

	ft_getsize(NULL, &bl->w);
	bx = (bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x;
	i = (bx - 1) / bl->w;
	if (i)
	{
		++bl->y;
		ft_putstr("\033[B");
		bl->cursor += bl->w;
		if (i - 1 == 0)
		{
			i = bx - (bl->w * i) - 1;
			if (bl->x > i)
			{
				bl->cursor = bl->len;
				ft_printf("\r\033[%dC", (bl->x = i));
				++bl->x;
			}
		}
	}
}

void		move_word(t_bufferl *bl, int c)
{
	if (c == 'D' && bl->cursor)
		move_d(bl);
	else if (c == 'C' && (int)bl->cursor < bl->len)
		move_c(bl);
	else if (c == 'A' && bl->y > bl->ys)
	{
		ft_putstr("\033[A");
		ft_getsize(NULL, &bl->w);
		bl->cursor -= bl->w;
		if (--bl->y == bl->ys && bl->x < bl->xs)
		{
			bl->cursor = 0;
			ft_printf("\r\033[%dC", (bl->x = bl->xs) - 1);
		}
	}
	else if (c == 'B')
		move_b(bl);
	else if (c == 'R' || c == 'S')
		selectmode(bl, c);
}
