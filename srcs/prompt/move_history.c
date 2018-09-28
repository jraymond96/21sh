/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 21:00:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/25 16:14:36 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"

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

static void	reprint_history(t_bufferl *bl, char *str)
{
	int		res;
	int		res1;
	char	halfc[8192];

	clean_line(bl);
	ft_strncpy(ft_strclr(bl->line), str, bl->size - 1);
	bl->line[bl->size - 1] = '\0';
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
		if (bl->ys + res >= bl->h)
			bl->ys -= bl->ys + res - bl->h + 1;
		bl->y = (bl->ys + res + 1 >= bl->h ? bl->h : bl->y + res + 1);
		bl->x = res1 % bl->w;
	}
	ft_putstr(ft_strrepc_str(ft_strcpy(halfc, bl->line), "\t\n", " ~"));
	if (bl->x == 1)
		ft_putchar('\n');
}

void		move_history(t_bufferl *bl, int c)
{
	if (c == 'B' && !bl->it->parent && bl->ni)
	{
		reprint_history(bl, bl->save);
		ft_memdel((void **)&bl->save);
		bl->ni = 0;
		return ;
	}
	if ((c == 'A' && ((!bl->ni && !bl->it) || (bl->ni && !bl->it->next)))
			|| (c == 'B' && !bl->it->parent))
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
