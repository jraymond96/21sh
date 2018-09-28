/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint_line3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 17:06:06 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/16 17:41:50 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readraw.h"
#include "ft_printf.h"
#include "shell.h"

static void	reprint_bis(t_bufferl *bl, t_slctmode *sm, int i)
{
	int	y;

	y = sm->save_y;
	ft_printf("\033[%d;%dH\033[s\033[K", sm->save_y, sm->save_x);
	while (++y <= bl->h)
		ft_printf("\033[%dE\033[2K", y);
	ft_printf("\033[u%#{white}%{black}%.*s%{0}", i,
				(bl->line + sm->save_cur));
	ft_printf("%s\033[%d;%dH", (bl->line + bl->cursor + 1),
				sm->save_y, sm->save_x);
}

void		reprint_line3(t_bufferl *bl, t_slctmode *sm)
{
	int	y;
	int	i;

	if ((i = bl->cursor - sm->save_cur) < 0)
		i *= -1;
	i++;
	ft_getsize(&bl->h, &bl->w);
	if (sm->save_cur > (int)bl->cursor)
	{
		y = bl->y;
		ft_printf("\033[%d;%dH\033[s\033[K", bl->y, bl->x);
		while (++y <= bl->h)
			ft_printf("\033[%dE\033[2K", y);
		ft_printf("\033[u%#{white}%{black}%.*s%{0}", i,
					(bl->line + bl->cursor));
		ft_printf("%s\033[u", (bl->line + sm->save_cur + 1));
	}
	else
		reprint_bis(bl, sm, i);
}

void		handle_xy_cursor(t_bufferl *bl, int left)
{
	ft_getsize(&bl->h, &bl->w);
	if (left == 1)
	{
		if (bl->cursor-- == 0)
		{
			bl->cursor = 0;
			return ;
		}
		bl->x = (bl->x == 1) ? bl->w : bl->x - 1;
		bl->y = (bl->x == bl->w) ? bl->y - 1 : bl->y;
	}
	else
	{
		if ((int)bl->cursor++ == bl->len - 1)
		{
			bl->cursor--;
			return ;
		}
		bl->x = (bl->x == bl->w) ? 1 : bl->x + 1;
		bl->y = (bl->x == 1) ? bl->y + 1 : bl->y;
	}
}
