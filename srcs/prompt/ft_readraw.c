/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 17:13:32 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 21:31:21 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"

static char	g_quote;

void		escape_char(t_bufferl *bl, int c)
{
	if ((c = (!c && ft_getch() ? ft_getch() : c)) == 'D' && bl->cursor != 0)
	{
		--bl->x;
		if (--bl->cursor && bl->x <= 0)
		{
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

static int	init_bl(t_bufferl *bl, char *line, size_t size)
{
	int	ny;

	if (!line)
	{
		g_quote = '\0';
		free(bl->save);
		ft_getsize(&bl->h, &bl->w);
		ny = ((bl->len + bl->xs) - (bl->cursor + bl->xs) + bl->x) / bl->w;
		ft_putstr("\033[?25h");
		while (ny--)
			ft_putchar('\n');
		return (0);
	}
	ft_bzero(bl, sizeof(t_bufferl));
	bl->it = g_shell->history;
	bl->line = line;
	bl->size = size;
	ft_getcursor(&bl->x, &bl->y);
	bl->ys = bl->y;
	bl->xs = bl->x;
	return (0);
}

static int	quote_char(t_bufferl *bl, int c)
{
	int	i;
	int	n;

	add_char(bl, c);
	if (c != '\'' && c != '"')
		return (0);
	if (g_quote && g_quote == c)
	{
		i = bl->cursor - 1;
		n = 0;
		while (--i >= 0 && bl->line[i] == '\\')
			++n;
		if (n % 2 == 0)
			g_quote = '\0';
	}
	else if (!g_quote)
		g_quote = c;
	return (0);
}

static int	end_bslash(t_bufferl *bl)
{
	int	i;
	int	n;

	n = 0;
	if (!g_quote && (i = bl->cursor - 1) >= 0
			&& bl->line[bl->cursor - 1] == '\\')
		while (--i >= 0 && bl->line[i] == '\\')
			++n;
	else
		n = -1;
	i = (int)g_quote;
	init_bl(bl, NULL, 0);
	g_quote = (char)i;
	ft_makeraw(0);
	if (g_quote || n % 2 == 0)
	{
		ft_putstr("\n> ");
		if (g_quote)
			bl->line[bl->cursor] = '\n';
		bl->line[(!g_quote ? --bl->cursor : ++bl->cursor)] = '\0';
		return (ft_readraw(bl->line + bl->cursor, bl->size - bl->cursor));
	}
	return (13);
}

int			ft_readraw(char *line, size_t size)
{
	int			c;
	t_bufferl	bl;

	init_bl(&bl, line, size);
	ft_makeraw(1);
	while ((c = ft_getch()))
	{
		if ((c == 3 || c == 4) && !init_bl(&bl, NULL, 0))
			break ;
		else if (c == 13)
			return (end_bslash(&bl));
		else if (c == 127 && !bl.sm)
			delete_char(&bl);
		else if (c == 27)
			escape_char(&bl, 0);
		else if (!bl.sm)
			quote_char(&bl, c);
		if (bl.sm)
			reprint_sm(&bl);
	}
	ft_makeraw(0);
	return (c);
}
