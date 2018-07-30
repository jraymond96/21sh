/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:44:03 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/23 20:57:03 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_types.h"

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

static void	movecursor(char *line, size_t *cursor)
{
	int	c;

	if ((c = ft_getch()) == '\033' && ft_getch() == '[')
		movecursor2(line, cursor, c);
	else if ((c = ft_getch()) == 'D' && *cursor != 0)
		ft_printf("\033[1D", --(*cursor));
	else if (c == 'C' && *cursor < ft_strlen(line))
		ft_printf("\033[1C", ++(*cursor));
	else if ((c == 'A' || c == 'B') && g_shell->history)
		movehistory(c, line, cursor);
	else if (c == 'F')
		ft_printf("\033[K", ft_strclr(line + *cursor));
	else if (c == 'H' || c == '3')
		movecursor3(c, line, cursor);
}

int			ft_readraw(char *line, size_t size)
{
	int		c;
	size_t	cursor;

	cursor = 0;
	ft_makeraw(1);
	while ((c = ft_getch()) && cursor < size - 1)
	{
		if (c == 3 || c == 4 || c == 13)
			break ;
		else if (c == 127)
			moveline(line, &cursor, 0, size);
		else if (c == '\033')
			movecursor(line, &cursor);
		else if (ft_isprint(c) || ft_isspace(c))
		{
			ft_putchar(c == '\t' ? ' ' : (char)c);
			if (line[cursor] != '\0')
				moveline(line, &cursor, 1, size);
			line[cursor++] = (char)c;
		}
	}
	ft_makeraw(0);
	ft_putchar('\n');
	return (c);
}
