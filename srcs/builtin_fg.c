/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:03:52 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/10 22:14:01 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_types.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

#include "../logger/incs/logger.h"
#include "errno.h"

static	t_list		*error_fg(char **argv, int i)
{
	if (!i)
		ft_printf_fd(2, "21sh: fg: %s: no such job\n", argv[1]);
	else
		ft_putstr_fd("21sh: fg: current: no such job\n", 2);
	return (NULL);
}

static	t_list		*check_args(int argc, char **argv, int numprocbg)
{
	int		x;
	t_list	*elem;

	x = -1;
	if (!(elem = g_shell->bgproc))
		return (error_fg(argv, 1));
	if (argc > 1)
	{
		while (argv[1][++x] && ft_isdigit(argv[1][x]))
			;
		if (argv[1][x] || numprocbg < 1)
			return (error_fg(argv, 0));
		while (elem && ((t_inffork *)elem->content)->x != numprocbg)
			elem = elem->next;
		handle_bgsign(elem, 0);
	}
	else
	{
		while (elem && ((t_inffork *)elem->content)->sign != '+')
			elem = elem->next;
	}
	if (elem && (((t_inffork *)elem->content)->status[0] != 'K' ||
				((t_inffork *)elem->content)->status[0] != 'D'))
		return (elem);
	return (error_fg(argv, 0));
}

static void			check_retfork(int ret, pid_t pid)
{
	if (WIFCONTINUED(ret))
		handle_bgstat(pid, BG_RUN);
	else if (WIFSTOPPED(ret))
	{
		if (WSTOPSIG(ret) == SIGTTIN)
			log_trace("ouiiiiiiiiiiii\n");
		handle_bgstat(pid, BG_STOP);
	}
	else if (!WIFEXITED(ret))
		handle_bgstat(pid, BG_KILL);
	else if (WIFEXITED(ret))
	{
		log_trace("end ok\n");
		handle_bgstat(pid, BG_END);
	}
}

int					builtin_fg(int argc, char **argv)
{
	t_list	*elem;
	int		status;

	if (!(elem = check_args(argc, argv, ft_atoi(argv[1]))))
		return (1);
	else
	{
		print_cmd_args2(((t_inffork *)elem->content)->cmd);
		signal(SIGCHLD, SIG_DFL);
		if (((t_inffork *)elem->content)->status[0] == 'S')
			kill(((t_inffork *)elem->content)->pid, SIGCONT);
		tcsetpgrp(0, ((t_inffork *)elem->content)->pid);
		waitpid(((t_inffork *)elem->content)->pid, &status, WUNTRACED);
		check_retfork(status, ((t_inffork *)elem->content)->pid);
		tcsetpgrp(0, getpgrp());
		signal(SIGCHLD, sign_child);
	}
	return (0);
}
