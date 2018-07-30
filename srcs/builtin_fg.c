/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:03:52 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 21:01:04 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_types.h"
#include <sys/wait.h>

static int		error_fg(char **argv, int i)
{
	if (!i)
		ft_printf_fd(2, "21sh: fg: %s: no such job\n", argv[1]);
	else
		ft_putstr_fd("21sh: fg: current: no such job\n", 2);
	return (-1);
}

char			**found_args_pid(int pid)
{
	int	x;

	x = -1;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x] && g_shell->bgproc[x]->pid == pid)
			break ;
	}
	if (x == (MAX_BGPROC - 1))
		return (NULL);
	else
		return (g_shell->bgproc[x]->cmd);
}

void			erase_bginfoproc(int x)
{
	int	i;

	i = -1;
	while (++i < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[i] &&
				g_shell->orderbg[x] == g_shell->bgproc[i]->pid)
			break ;
	}
	if (i == MAX_BGPROC - 1)
		return ;
	ft_delenv(&g_shell->bgproc[i]->cmd);
	ft_memdel((void **)&g_shell->bgproc[i]);
	deli_shiftend(g_shell->orderbg[x], (MAX_BGPROC - 1));
}

int				specified_fg(char **argv, int bg_x)
{
	int	x;
	int	save;

	x = -1;
	save = g_shell->curpid;
	while (argv[1][++x] && ft_isdigit(argv[1][x]))
		;
	if (argv[1][x] || bg_x > 20 || bg_x < 1)
		return (error_fg(argv, 0));
	x = -1;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x] && g_shell->bgproc[x]->x == bg_x)
		{
			print_cmd_args2(found_args_pid(g_shell->orderbg[x]));
			g_shell->curpid = g_shell->orderbg[x];
			erase_bginfoproc(x);
			waitpid(g_shell->curpid, NULL, 0);
			g_shell->curpid = save;
			break ;
		}
	}
	if (x == (MAX_BGPROC - 1))
		return (error_fg(argv, 0));
	return (0);
}

int				builtin_fg(int argc, char **argv)
{
	int	x;
	int	save;

	x = -1;
	save = g_shell->curpid;
	if (argc > 1)
	{
		if (specified_fg(argv, ft_atoi(argv[1])) == -1)
			return (-1);
		return (0);
	}
	while (++x < (MAX_BGPROC - 1) && g_shell->orderbg[x + 1] != 0)
		;
	if (x == (MAX_BGPROC - 1))
		return (error_fg(argv, 1));
	else
	{
		print_cmd_args2(found_args_pid(g_shell->orderbg[x]));
		g_shell->curpid = g_shell->orderbg[x];
		erase_bginfoproc(x);
		waitpid(g_shell->curpid, NULL, 0);
		g_shell->curpid = save;
	}
	return (0);
}
