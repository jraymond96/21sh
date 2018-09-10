/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 18:19:36 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/09 18:48:25 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_types.h"

#include "../logger/incs/logger.h"

static int	y;

static void	moveline(char *line, size_t *cursor, int direction, size_t size)
{
	size_t	i;
	char	*str;

	if (!direction && !*cursor)
		return ;
	i = (direction ? ft_strlen(line) : --(*cursor));
	while (((direction == 0 && line[i])
		|| (direction && i >= *cursor && i > 0)) && i < size)
	{
		line[i] = line[i + (direction ? -1 : 1)];
		i += (direction ? -1 : 1);
	}
	str = ft_strrep(&line[*cursor + (direction ? 1 : 0)], '\t', ' ');
	if (direction)
		ft_printf("%s\033[%dD", str,
				ft_strlen(line) - *cursor - 1);
	else
		ft_printf("\033[1D%s \033[%dD", str,
				ft_strlen(line) - *cursor + 1);
	free(str);
}

static void	movecursor2(char *line, size_t *cr, int c)
{
	int	pos;

	pos = -1;
	if ((c = ft_getch()) && *cr && ft_strchr("DCBA", c))
		ft_printf("\033[%dD", *cr);
	if (c == 'D' || c == 'C')
	{
		if (c == 'D')
			pos = ft_strnrpbrk_pos(line, " \t", (*cr && *cr - 1 ? *cr - 2 : 0));
		else
			pos = ft_strpbrk_pos(line + (*cr + 1), " \t");
		if (pos != -1)
			ft_printf("\033[%dC",
				*cr = (c == 'D' ? (size_t)pos + 1 : *cr + (size_t)pos + 2));
		else if (c == 'D' || (*cr = ft_strlen(line)))
			(c == 'D' ? *cr = 0 : (size_t)ft_printf("\033[%dC", *cr));
		if (c == 'D')
			while (*cr && ft_strchr(" \t", line[*cr]))
				ft_printf("\033[1D", --*cr);
		else
			while (line[*cr] && ft_strchr(" \t", line[*cr]))
				ft_printf("\033[1C", ++*cr);
	}
	else if (c == 'B' || (c == 'A' && (*cr = ft_strlen(line))))
		(c == 'A' ? (size_t)ft_printf("\033[%dC", *cr) : (*cr = 0));
}
/*
static void	movecursor3(int c, char *line, size_t *cursor)
{
	size_t	n;

	if (*cursor)
		ft_printf("\033[%dD", *cursor);
	ft_printf("\033[K");
	if (c == 'H')
	{
		n = ft_strlen(line + *cursor);
		ft_memmove(line, line + *cursor, n);
		ft_putstr(ft_strclr(line + n) - n);
		if ((*cursor = ft_strlen(line)))
			ft_printf("\033[%dD", *cursor);
		*cursor = 0;
	}
	else if (c == '3' && ft_getch() && ft_strclr(line))
		*cursor = 0;
}
*/
static void	movecursor(char *line, size_t *cursor, int *x)
{
	int				c;
	int				s;

	if ((c = ft_getch()) == '\033' && ft_getch() == '[')
		movecursor2(line, cursor, c);
	else if ((c = ft_getch()) == 'D' && *cursor != 0)
	{
		if (--(*x) <= 0)
		{
			ft_getsize(NULL, x);
			--y;
			if (y < 1)
				--(*x);
			ft_printf("\033[A\033[%dC", *x, --(*cursor));
			log_trace("x: %d\n", *x);
		}
		else
			ft_printf("\033[1D", --(*cursor));
	}
	else if (c == 'C' && *cursor < ft_strlen(line))
	{
		ft_getsize(NULL, &s);
		if (*x <= s - (y ? 1 : 2))
			ft_printf("\033[1C", ++(*cursor), ++(*x));
		else
		{
			++y;
			*x = 1;
			ft_printf("\n", ++(*cursor));
		}
	}
/*	else if ((c == 'A' || c == 'B') && g_shell->history)
		movehistory(c, line, cursor);
	else if (c == 'F')
		ft_printf("\033[K", ft_strclr(line + *cursor));
	else if (c == 'H' || c == '3')
		movecursor3(c, line, cursor);*/
}

int			ft_readraw(char *line, size_t size)
{
	int		c;
	size_t	cursor;
	int		x;
	int		s;

	ft_getcursor(&x, NULL);
	cursor = 0;
	y = 0;
	ft_makeraw(1);
	while ((c = ft_getch()) && cursor < size - 1)
	{
	log_trace("Before_cursor: %d %d %d\n", cursor, x, y);
		if (c == 3 || c == 4 || c == 13)
			break ;
		else if (c == 127)
		{
			if (--x <= 0)
			{
				ft_getsize(NULL, &x);
				--y;
				if (y < 1)
					--x;
			}
			moveline(line, &cursor, 0, size);
		}
		else if (c == '\033')
			movecursor(line, &cursor, &x);
		else if (ft_isprint(c) || ft_isspace(c))
		{
			ft_putchar(c == '\t' ? ' ' : (char)c);
			if (line[cursor] != '\0')
				moveline(line, &cursor, 1, size);
			ft_getsize(NULL, &s);
			if (++x > s)
			{
				++y;
				x = 1;
				log_debug("cursor ok\n");
				ft_printf("\n");
			}
			line[cursor++] = (char)c;
		}
	log_trace("After_cursor: %zd %d %d\n", cursor, x, y);
	}
	ft_makeraw(0);
	ft_putchar('\n');
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:44:03 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/05 18:18:34 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
typedef struct		s_linesave
{
	char			**line;
	int				startx;
	int				cursor;
	int				len;
}					t_linesave;

static void	escape_char(t_linesave *ln)
{
	int	c;

	if ((c = ft_getch()) == '[')
	{
		if ((c = ft_getch()) == 'D' && ln->lines->cursor)
		{
			ft_putstr("\033[D");
			--ln->lines->cursor;
		}
		else if (c == 'C' && ln->lines->cursor < ln->lines->len)
		{
			ft_putstr("\033[C");
			++ln->lines->cursor;
		}
	}
	(void)ln;
}

static void	delete_char(t_linesave *ln)
{
	int	w;

	if (ln->lines->cursor)
	{
		ft_getsize(NULL, &w);
		ft_strerase(ln->lines->line, ln->lines->cursor - 1, 1);
		--ln->lines->len;
		if (ln->lines->off)
			--ln->lines->off;
		--ln->lines->cursor;
		if (ln->lines->len + 1)
			reprint_line(ln);
	}
}

static void	add_char(t_linesave *ln, int c)
{
	char	*tmp;
	int		w;

	tmp = *ln->line;
	*ln->line = ft_strmdup(tmp, 1);
	free(tmp);
	ft_strinsert(*ln->line, &c, ln->cursor++, 1);
	++ln->len;
	ft_getsize(NULL, &w);
	ft_putchar('\r');
	if (ln->lines->startx)
		ft_printf("\033[%dC", ln->startx);
	ft_putstr("\033[K");
	ft_printf("%s\033[%dD", ln->line, ln->len - ln->cursor + 1);
}

int	ft_readraw2(char **line)
{
	int			c;
	t_linesave	ln;

	ft_bzero(&ln, sizeof(t_linesave));
	ln.line = line;
	ft_getcursor(NULL, &ln.lines->startx);
	ft_makeraw(1);
	while ((c = ft_getch()))
	{
		if (c == 27)
			escape_char(&ln);
		else if (c == 127)
			delete_char(&ln);
		else if (c == 3 || c == 4 || c == 13)
			break ;
		else
			add_char(&ln, c);
	}
	ft_makeraw(0);
	return (c);
}
*/
typedef struct		s_line
{
	char			*line;
	int				len;
	int				cursor;
	int				startx;
	int				off;
	int				y;
	struct s_line	*next;
	struct s_line	*parent;
}					t_line;

typedef struct		s_linesave
{
	t_line			*lines;
	int				x;
	int				y;
	int				ny;
	int				cursor;
	int				len;
}					t_linesave;

static void	escape_char(t_linesave *ln)
{
	int	c;

	if ((c = ft_getch()) == '[')
	{
		if ((c = ft_getch()) == 'D' && ln->lines->cursor)
		{
			ft_putstr("\033[D");
			--ln->lines->cursor;
		}
		else if (c == 'C' && ln->lines->cursor < ln->lines->len)
		{
			ft_putstr("\033[C");
			++ln->lines->cursor;
		}
	}
	(void)ln;
}
/*
static void reprint_line(t_linesave *ln, int n)
{
	ft_putchar('\r');
	if (ln->lines->startx)
		ft_printf("\033[%dC", ln->lines->startx);
	ft_putstr("\033[K");
	if (ln->lines->off)
		ft_printf("%c%s\033[%dD", '*', ln->lines->line + ln->lines->off + 1,
				ln->lines->len - ln->lines->cursor);
	else
		ft_printf("%s\033[%dD", ln->lines->line, ln->lines->len - ln->lines->cursor + n);
}*/

static void	delete_char(t_linesave *ln)
{
	int	w;

	if (ln->lines->cursor)
	{
		ft_getsize(NULL, &w);
		ft_strerase(ln->lines->line, ln->lines->cursor - 1, 1);
		--ln->lines->len;
		if (ln->lines->off)
			--ln->lines->off;
		--ln->lines->cursor;
		if (ln->lines->len + 1)
		{
			ft_putchar('\r');
			if (ln->lines->startx)
				ft_printf("\033[%dC", ln->lines->startx);
			ft_putstr("\033[K");
			if (ln->lines->off)
				ft_printf("%c%s\033[%dD\033[%dC", '*', ln->lines->line + ln->lines->off,
						ln->lines->len - ln->lines->off, ln->lines->cursor);
			else
				ft_printf("%s\033[%dD\033[%dC", ln->lines->line, ln->lines->len, ln->lines->cursor);
		}
	}
}

/*static void	add_char(t_linesave *ln, int c)
{
	char	*tmp;
	int		w;

	tmp = ln->lines->line;
	ln->lines->line = ft_strmdup(tmp, 1);
	free(tmp);
	ft_strinsert(ln->lines->line, (char *)&c, ln->lines->cursor++, 1);
	++ln->lines->len;
	ft_getsize(NULL, &w);
	if (ln->lines->len >= w - ln->lines->startx)
		++ln->lines->off;
	ft_putchar('\r');
	if (ln->lines->startx)
		ft_printf("\033[%dC", ln->lines->startx);
	ft_putstr("\033[K");
	if (ln->lines->off)
		ft_printf("%c%s\033[%dD", '*', ln->lines->line + ln->lines->off + 1,
				ln->lines->len - ln->lines->cursor - 1);
	else
		ft_printf("%s\033[%dD", ln->lines->line, ln->lines->len - ln->lines->cursor - 1);
}

int	ft_readraw2(char **line)
{
	int			c;
	t_linesave	ln;

	ft_bzero(&ln, sizeof(t_linesave));
	ln.lines = ft_memalloc(sizeof(t_line));
	ln.lines->line = ft_strnew(0);
	ft_getcursor(&ln.x, &ln.y);
	--ln.x;
	++ln.ny;
	ln.lines->startx = ln.x;
	ft_makeraw(1);
	while ((c = ft_getch()))
	{
		if (c == 27)
			escape_char(&ln);
		else if (c == 127)
			delete_char(&ln);
		else if (c == 3 || c == 4 || c == 13)
			break ;
		else
			add_char(&ln, c);
	}
	ft_makeraw(0);
	*line = ln.lines->line;
	return (c);
}*/
