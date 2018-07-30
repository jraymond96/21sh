/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bgstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 13:31:39 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 21:53:31 by jraymond         ###   ########.fr       */
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
	{BG_RUN, "Running"}, {BG_KILL, "Killed"},
	{BG_END, "Done"}, {BG_STOP, "Suspended"},
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

int						handle_bgstat(pid_t pid, int status, int num_proc)
{
	t_list	*elem;
	size_t	i;

	i = -1;
	elem = g_shell->bgproc;
	while (elem && elem->content->pid != pid)
		elem = elem->next;
	while (++i < g_bgstats_size)
	{
		if (status == g_bgstat[i].status)
		{
			ft_strcpy(elem->content->status, g_bgstat[i].message);
			break ;
		}
	}
	return (0);
}
