/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:13:32 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 23:17:43 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"

#include "../logger/incs/logger.h"

static void	clean_line(t_bufferl *bl)
{
	int	res;
	int	i;

	ft_printf("\033[%d;%dH", bl->ys, bl->xs);
	ft_getsize(&bl->h, &bl->w);
//	ft_putstr("\033[J");
	(void)i;
	ft_putstr("\033[s");
	res = bl->h;
	res -= bl->ys;
	bl->y = bl->ys;
	bl->x = bl->xs;
	i = 0;
	while (i++ <= res)
		ft_putstr("\033[K\033[B\r");
	ft_putstr("\033[u");
}

static void	reprint_line(t_bufferl *bl)
{
	int	ny;
	int	ny2;
	int	ny3;
	char	halfc[8192];

	ft_getsize(&bl->h, &bl->w);
	ny = (bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x;
	ny2 = (ny - 1) / bl->w;
	ny3 = ny - (bl->w * ny2);
//	log_debug("trolol: %d %d %d %d %d\n", bl->y + ny2, bl->h, ny3, ny2, ny);
	ft_strrepc(ft_strcpy(halfc, bl->line + (bl->cursor - 1)), '\t', ' ');
	if (bl->y + ny2 > bl->h && ny3 == 1)
	{
		--bl->ys;
		ft_printf("\033[s%s\033[u\033[A\033[C", halfc);
	}
	else
		ft_printf("\033[s%s\033[u\033[C", halfc);
}

static void	delete_char(t_bufferl *bl)
{
	int	x;
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
		ft_strrepc(ft_strcpy(halfc, bl->line + bl->cursor), '\t', ' ');
		ft_printf("\033[s%s\033[K", halfc);
		if (bl->y < bl->h)
			ft_printf("\033[B\r\033[K\033[u%s", halfc);
		ft_putstr("\033[u");
	}
}

static void	add_char(t_bufferl *bl, int c)
{
	ft_getsize(&bl->h, &bl->w);
//	log_debug("lol: w:%d x:%d\n", bl->w, bl->x);
	ft_strinsert(bl->line, (char *)&c, bl->cursor++, 1);
	bl->line[bl->len + 1] = '\0';
	if ((int)bl->cursor == ++bl->len)
		ft_putchar(c == '\t' ? ' ' : c);
	else
		reprint_line(bl);
	if (++bl->x > bl->w)
	{
		bl->x = 1;
		if (++bl->y > bl->h)
		{
			--bl->ys;
			--bl->y;
		}
//		log_debug("yeeeeeees: w:%d x:%d\n", bl->w, bl->x);
		ft_putstr("\n");
	}
}

static void	reprint_history(t_bufferl *bl, char *str)
{
	int		res;
	int		res1;
	int		res2;
	char	halfc[8192];

	res2 = 0;
	(void)res2;
//	log_trace("111111111111: xs: %d | ys: %d\n", bl->xs, bl->ys);
	clean_line(bl);
	ft_strcpy(ft_strclr(bl->line), str);
	bl->len = ft_strlen(str);
	res1 = bl->len;
	bl->cursor = bl->len;
	res = bl->len - (bl->w - bl->xs);
	if (res <= 0)
		bl->x = bl->xs + bl->len;
	else
	{
		res1 -= (bl->w - bl->xs);
		res = res1 / bl->w;
		if (bl->ys + res >= bl->h)
		{
			bl->y = bl->h;
			bl->ys -= bl->ys + res - bl->h + 1;
		}
		else
			bl->y += ++res;
		res = res1 % bl->w;
		bl->x = res;
	}
	ft_putstr(ft_strrepc(ft_strcpy(halfc, bl->line), '\t', ' '));
}

static void	move_history(t_bufferl *bl, int c)
{
	if (c == 'B' && !bl->it->parent && bl->ni)
	{
		reprint_history(bl, bl->save);
		ft_memdel((void **)&bl->save);
		bl->ni = 0;
		return ;
	}
	if ((c == 'A' && !bl->it->next) || (c == 'B' && !bl->it->parent))
		return ;
	if (bl->ni)
	{
		if (c == 'A')
			bl->it = bl->it->next;
		else if (c == 'B')
		{
			bl->it = bl->it->parent;
		}
	}
	else
	{
		bl->save = ft_strdup(bl->line);
		bl->ni = 1;
	}
	reprint_history(bl, (char *)bl->it->content);
}

static void	move_word(t_bufferl *bl, int c)
{
	int	pos;
	int	bx;
	int	i;

	if (c == 'D' && bl->cursor)
	{
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
//			log_debug("Okkkmdr %d\n", bl->x);
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
	else if (c == 'C' && (int)bl->cursor < bl->len)
	{
		ft_getsize(NULL, &bl->w);
		i = 1;
		while ((pos = ft_strpbrk_pos(bl->line + bl->cursor + i, " \t")) == 0)
			++i;
		if (pos == -1)
			pos = bl->len - 1;
		else
			pos += bl->cursor + (i - 1);
//		log_debug("right move: %d %d '%s'\n", bl->x, bl->w, bl->line + bl->cursor + 2);
		bx = bl->x;
		if ((bl->x += pos - (bl->cursor)) > bl->w)
		{
			bl->cursor += bl->w - bx;
			if (bl->w - bx)
				ft_printf("\033[%dC", bl->w - bx);
			bl->x = bl->w;
		}
		else
		{
			bl->cursor = pos;
			ft_printf("\r\033[%dC", bl->x - 1);
		}
	}
	else if (c == 'R' || c == 'S')
		selectmode(bl, c);
}

static void	escape_char(t_bufferl *bl)
{
	int	c;

	ft_getch();
	if ((c = ft_getch()) == 'D' && bl->cursor != 0)
	{
		--bl->cursor;
		if (--bl->x <= 0)
		{
			--bl->y;
			ft_getsize(NULL, &bl->x);
			ft_printf("\033[A\033[%dC", bl->x);
		}
		else
			ft_putstr("\033[D");
	}
	else if (c == 'C' && (int)bl->cursor < bl->len)
	{
		++bl->cursor;
		ft_getsize(NULL, &bl->w);
		if (++bl->x > bl->w)
		{
			bl->x = 1;
			++bl->y;
			ft_putstr("\n");
		}
		else
			ft_putstr("\033[C");
	}
	else if ((c == 'A' || c == 'B') && g_shell->history)
		move_history(bl, c);
	else if (c == '1' && ft_getch() == ';' && ft_getch() == '2')
		move_word(bl, ft_getch());
}


static void	init_bl(t_bufferl *bl, char *line, size_t size)
{
	bl->it = g_shell->history;
	bl->ni = 0;
	bl->line = line;
	bl->size = size;
	bl->cursor = 0;
	bl->len = 0;
	ft_getcursor(&bl->x, &bl->y);
	bl->ys = bl->y;
	bl->xs = bl->x;
	bl->save = NULL;
}

static void	go_bottom(t_bufferl *bl)
{
	int	ny;

	ft_getsize(&bl->h, &bl->w);
	ny = ((bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x) / bl->w;
	while (ny--)
		ft_putchar('\n');
}

int	ft_readraw3(char *line, size_t size)
{
	int			c;
	t_bufferl	bl;

	init_bl(&bl, line, size);
	ft_makeraw(1);
	while ((c = ft_getch()))
	{
//		log_debug("char: %d %c\n", c, c);
//		log_trace("current: x:%d y:%d s(%d %d) cursor:%d len:%d\n", bl.x, bl.y, bl.ys, bl.xs, bl.cursor, bl.len);
		if (c == 3 || c == 4 || c == 13)
		{
			go_bottom(&bl);
			break ;
		}
		else if (c == 127)
			delete_char(&bl);
		else if (c == 27)
			escape_char(&bl);
		else
			add_char(&bl, c);
//		log_trace("current after: x:%d y:%d s(%d %d) cursor:%d len:%d\n", bl.x, bl.y, bl.ys, bl.xs, bl.cursor, bl.len);
	}
	ft_makeraw(0);
	free(bl.save);
	return (c);
}
