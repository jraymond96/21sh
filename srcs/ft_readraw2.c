/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:13:32 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 19:42:30 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"

#include "../logger/incs/logger.h"

static char	*line_sm;

static void	clean_line(t_bufferl *bl)
{
	int	res;
	int	i;

	ft_printf("\033[%d;%dH", bl->ys, bl->xs);
	ft_getsize(&bl->h, &bl->w);
	ft_putstr("\033[s");
	res = bl->h - bl->ys;
	bl->y = bl->ys;
	bl->x = bl->xs;
	i = 0;
	while (i++ <= res)
		ft_putstr("\033[K\033[B\r");
	ft_putstr("\033[u");
}

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
//	log_debug("trolol: %d %d %d %d %d\n", bl->y + ny2, bl->h, ny3, ny2, ny);
	ft_strrepc(ft_strcpy(halfc, bl->line + (bl->cursor - 1)), '\t', ' ');
	if (bl->y + ny2 > bl->h && ny3 == 1)
	{
		--bl->ys;
		--bl->y;
		ft_printf("\033[s%s\033[u\033[A\033[C", halfc);
	}
	else
		ft_printf("\033[s%s\033[u\033[C", halfc);
}

static void	delete_char(t_bufferl *bl)
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
		ft_strrepc(ft_strcpy(halfc, bl->line + bl->cursor), '\t', ' ');
		ft_printf("\033[s%s\033[K", halfc);
		if (bl->y < bl->h)
			ft_printf("\033[B\r\033[K\033[u%s", halfc);
		ft_putstr("\033[u");
	}
}

void		add_char(t_bufferl *bl, int c)
{
//	log_debug("xs: %d | ys: %d | x: %d | y: %d | cursor: %d\n", bl->xs, bl->ys, bl->x, bl->y, bl->cursor);
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
//		log_debug("yeeeeeees: w:%d x:%d\n", bl->w, bl->x);
		ft_putstr("\n");
	}
//	log_debug("xs: %d | ys: %d | x: %d | y: %d | cursor: %d\n", bl->xs, bl->ys, bl->x, bl->y, bl->cursor);
}

static void	reprint_history(t_bufferl *bl, char *str)
{
	int		res;
	int		res1;
	char	halfc[8192];

	clean_line(bl);
	ft_strncpy(ft_strclr(bl->line), str, bl->size);
	bl->len = ft_strlen(bl->line);
	res1 = bl->len;
	bl->cursor = bl->len;
	res = bl->len - (bl->w - bl->xs);
	if (res <= 0)
		bl->x = bl->xs + bl->len;
	else
	{
		res1 -= (bl->w - bl->xs);
		res = res1 / bl->w;
		bl->y = (bl->ys + res >= bl->h ? bl->h : res + 1);
		if (bl->ys + res >= bl->h)
			bl->ys -= bl->ys + res - bl->h + 1;
		bl->x = res1 % bl->w;
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
		bl->it = (c == 'A' ? bl->it->next : bl->it->parent);
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
			pos += (bl->cursor ? (int)bl->cursor + (i - 1) : 0);
		bx = bl->x;
		if ((bl->x += pos - bl->cursor) > bl->w)
		{
//			log_debug("11111111111111111111\n");
			bl->cursor += bl->w - bx;
			if (bl->w - bx)
				ft_printf("\033[%dC", bl->w - bx);
			bl->x = bl->w;
		}
		else
		{
//			log_debug("22222222222222222\n");
			bl->cursor = pos;
			ft_printf("\r\033[%dC", bl->x - 1);
		}
	}
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
	{
		ft_getsize(NULL, &bl->w);
		bx = (bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x;
		i = (bx - 1) / bl->w;
//		log_debug("last next: %d\n", i);
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
	else if (c == 'R' || c == 'S')
		selectmode(bl, c);
}

static void	escape_char(t_bufferl *bl, int c);

static void	move_end(t_bufferl *bl, int c)
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
	else if (ft_getch() == '~')
	{
		if (c == '5')
		{
			if (bl->sm)
			{
				bl->sm = 0;
				ft_printf("\033[?25h\033[s%{0}\033[%d;%dH%s\033[u", bl->ys, bl->xs, bl->line);
			}
			else
			{
				if ((int)bl->cursor == bl->len)
					escape_char(bl, 'D');
				ft_putstr("\033[?25l");
				bl->sm_x = bl->x;
				bl->sm_y = bl->y;
				bl->sm_cursor = bl->cursor;
				bl->sm = 1;
			}
		}
		else if (c == '6')
		{
			if (!bl->sm && line_sm)
			{
				char	*it = line_sm;
				while (*it)
				{
					add_char(bl, (int)*it);
					++it;
				}
			}
			else if (bl->sm)
			{
				free(line_sm);
				if (bl->cursor > bl->sm_cursor)
					line_sm = ft_strndup(bl->line + bl->sm_cursor, bl->cursor - bl->sm_cursor + 1);
				else if (bl->sm_cursor > bl->cursor)
					line_sm = ft_strndup(bl->line + bl->cursor, bl->sm_cursor - bl->cursor + 1);
				else
					line_sm = ft_strndup(bl->line + bl->cursor, 1);
			}
		}
	}
}

static void	escape_char(t_bufferl *bl, int d)
{
	int	c;

	if (!d && ft_getch())
		c = ft_getch();
	else
		c = d;
	if (c == 'D' && bl->cursor != 0)
	{
		--bl->x;
		if (--bl->cursor && bl->x <= 0)
		{
//			log_debug("HELLO\n");
			ft_getsize(NULL, &bl->x);
			ft_printf("\033[A\033[%dC", bl->x, --bl->y);
		}
		else
			ft_putstr("\033[D");
	}
	else if (c == 'C' && (int)bl->cursor < bl->len)
	{
		ft_getsize(NULL, &bl->w);
		if (++bl->cursor && ++bl->x > bl->w)
			ft_printf("\n", (bl->x = 1), ++bl->y);
		else
			ft_putstr("\033[C");
	}
	else if ((c == 'A' || c == 'B') && g_shell->history)
		move_history(bl, c);
	else if (c == 'H' || c == 'F' || c == '5' || c == '6')
		move_end(bl, c);
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
	bl->sm = 0;
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
	ft_putstr("\033[?25h");
	while (ny--)
		ft_putchar('\n');
}

static void	reprint_sm(t_bufferl *bl)
{
//	log_debug("selection: %d %d ", bl->cursor, bl->sm_cursor);
	if (bl->cursor > bl->sm_cursor)
	{
		if ((int)bl->cursor == bl->len)
			escape_char(bl, 'D');
//		log_debug("BEG: %.*s\n", bl->cursor - bl->sm_cursor + 1, bl->line + bl->sm_cursor);
		ft_printf("\033[s%{0}\033[%d;%dH%.*s", bl->ys, bl->xs, bl->sm_cursor, bl->line);
		ft_printf("%#{white}%{black}%.*s", bl->cursor - bl->sm_cursor + 1, bl->line + bl->sm_cursor);
		ft_printf("%{0}%s\033[u", bl->line + bl->cursor + 1);
	}
	else if (bl->sm_cursor >= bl->cursor)
	{
//		log_debug("END: %.*s\n", bl->sm_cursor - bl->cursor + 1, bl->line + bl->cursor);
		ft_printf("\033[s%{0}\033[%d;%dH%.*s", bl->ys, bl->xs, bl->cursor, bl->line);
		ft_printf("%#{white}%{black}%.*s",
			bl->sm_cursor - bl->cursor + 1, bl->line + bl->cursor);
		ft_printf("%{0}%s\033[u", bl->line + bl->sm_cursor + 1);
	}
	else
	{
//		log_debug("mDRRROKKK\n");
		ft_printf("\033[s%{0}\033[%d;%dH%.*s\033[u", bl->ys, bl->xs, bl->cursor, bl->line);
	}
}

int	ft_readraw3(char *line, size_t size)
{
	int			c;
	t_bufferl	bl;

	init_bl(&bl, line, size);
	ft_makeraw(1);
	while ((c = ft_getch()))
	{
//		log_trace("current: x:%d y:%d s(%d %d) cursor:%d len:%d\n", bl.x, bl.y, bl.ys, bl.xs, bl.cursor, bl.len);
		if (c == 3 || c == 4 || c == 13)
		{
			go_bottom(&bl);
			break ;
		}
		else if (c == '\t')
			completion(&bl);
		else if (c == 127 && !bl.sm)
			delete_char(&bl);
		else if (c == 27)
			escape_char(&bl, 0);
		else if (!bl.sm)
			add_char(&bl, c);
		if (bl.sm)
			reprint_sm(&bl);
//		log_trace("current after: x:%d y:%d s(%d %d) cursor:%d len:%d\n", bl.x, bl.y, bl.ys, bl.xs, bl.cursor, bl.len);
	}
	ft_makeraw(0);
	free(bl.save);
	return (c);
}
