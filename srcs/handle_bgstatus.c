/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bgstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:31:39 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/18 20:46:04 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"
#include "ft_mem.h"

/*
** x de end_status a 1 direct pour sauter le Running car c est pas un
** fin de proc;
*/

static	t_bgstats		g_bgstat[] = {
	{BG_RUN, "Running"}, {BG_KILL, "Terminated"},
	{BG_END, "Done"},
};

static size_t			g_bgstats_size = sizeof(g_bgstat) / sizeof(t_bgstats);

int			end_status(char *str)
{
	size_t x;

	x = 0;
	while (++x < g_bgstats_size)
	{
		if (ft_strcmp(str, g_bgstat[x].message) == 0)
			return (x);
	}
	return (-1);
}

void					check_bg(void)
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

int						handle_bgstat(pid_t pid, int status)
{
	int		x;
	size_t	i;

	x = -1;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x] && g_shell->bgproc[x]->pid == pid)
			break ;
	}
	if (x == (MAX_BGPROC - 1))
		return (-1);
	else
	{
		i = -1;
		while (++i < g_bgstats_size)
		{
			if (status == g_bgstat[i].status)
			{
				ft_strcpy(g_shell->bgproc[x]->status, g_bgstat[i].message);
				break ;
			}
		}
	}
	return (0);
}
