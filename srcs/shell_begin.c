/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 22:32:53 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_io.h"
#include "ft_types.h"
#include "ft_list.h"
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <sys/signal.h>
#include <sys/wait.h>

#include "../logger/incs/logger.h"

void	sign_child(int sign)
{
	t_list	*elem;
	pid_t	pid;
	int		ret;

	elem = g_shell->bgproc;
	while (elem)
	{
		pid = ((t_inffork *)elem->content)->pid;
		if (sign == SIGCHLD && waitpid(pid, &ret, WNOHANG | WUNTRACED) == pid)
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
		elem = elem->next;
	}
}

static	void	sign_handler(int sign)
{
	char	*tmp;

	(void)sign;
	if (sign == -1)
	{
		signal(SIGINT, sign_handler);
		signal(SIGWINCH, sign_handler);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGCHLD, sign_child);
	}
	if (sign == SIGINT)
	{
		g_shell->kill_builtin = 1;
		if (g_shell->script)
			exit(0);
	}
	else if (sign == SIGWINCH)
	{
		ft_getsize(&g_shell->height, &g_shell->width);
		ft_setenv("LINES", (tmp = ft_itoa(g_shell->height)), &g_shell->envp);
		free(tmp);
		ft_setenv("COLUMNS", (tmp = ft_itoa(g_shell->width)), &g_shell->envp);
		free(tmp);
	}
}

static	void	initenvp(char **envp)
{
	int	i;

	if (!(g_shell->envp =
				(char **)malloc(sizeof(char *) * (ft_tabsize(envp) + 1))))
		ft_exit(EXIT_FAILURE, "Failed to copy 'envp'. Exiting\n");
	i = 0;
	while (*envp)
	{
		if (ft_strmatch(*envp, "USER=*"))
			g_shell->user = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "HOME=*"))
			g_shell->homepwd = ft_strchr(*envp, '=') + 1;
		if (!(g_shell->envp[i++] = ft_strdup(*envp)))
			ft_exit(EXIT_FAILURE, "Failed to copy 'envp'. Exiting\n");
		++envp;
	}
	g_shell->envp[i] = NULL;
}

int				shell_begin(char *name, int argc, char **argv, char **envp)
{
	static	t_args	args;
	char			*tmp;

	sign_handler(-1);
	if (!(g_shell = (t_shell *)ft_memalloc(sizeof(t_shell))))
		ft_exit(EXIT_FAILURE, "Failed to begin shell. Exiting\n");
	setlocale(LC_ALL, "");
	init_gshell(envp, name);
	args.argc = argc;
	args.argv = argv;
	g_shell->curargs = &args;
	initenvp(envp);
	ft_bzero(g_shell->pwd, 2048);
	if ((tmp = ft_getenv("PWD", g_shell->envp)))
		ft_strcpy(g_shell->pwd, tmp);
	else
		ft_strcpy(g_shell->pwd, ft_getcwd(NULL, 0));
	ft_setenv("SHLVL",
			(tmp = ft_itoa(ft_atoi(ft_getenv("SHLVL", g_shell->envp)) + 1)),
			&g_shell->envp);
	free(tmp);
	sign_handler(SIGWINCH);
	return (shell_init(argc, argv));
}
