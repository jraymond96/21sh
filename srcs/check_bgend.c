/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bgend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:04:49 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/19 16:27:20 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_io.h"

void					check_bgend(void)
{
	size_t	x;
	int		y;

	x = -1;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x] && end_status(g_shell->bgproc[x]->status) != -1)
		{
			ft_printf("[%d]  %c %s", g_shell->bgproc[x]->x,
						g_shell->bgproc[x]->sign, g_shell->bgproc[x]->status);
			y = -1;
			while (g_shell->bgproc[x]->cmd[++y])
				ft_printf(" %s", g_shell->bgproc[x]->cmd[y]);
			ft_putchar('\n');
			ft_delenv(&g_shell->bgproc[x]->cmd);
			ft_memdel((void **)&g_shell->bgproc[x]);
		}
	}
}
