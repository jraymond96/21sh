/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:24:43 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 19:05:58 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

static	pid_t	g_pid;
static	int		g_status;

struct	s_numerror
{
	int		num;
	char	*message;
};

typedef struct s_numerror	t_numerr;

enum	e_error
{
	ERR_FORK, ERR_SETPGID, ERR_EXEC, ERR_SIGTSTP,
	ERR_SIGCHLD, ERR_WAITPID, ERR_TSETPGRP, ERR_OK, ERR_SIGQUIT,
};

typedef enum e_error	t_error;

static t_numerr g_error [] = {
	{ERR_FORK, "fork error: "}, {ERR_SETPGID, "setpgid error: "},
	{ERR_EXEC, "execve error: "}, {ERR_WAITPID, "waitpid error: "},
	{ERR_SIGTSTP, "signal error: failed to catch SIGTSTP\n"},
	{ERR_SIGCHLD, "signal error: failed to catch SIGCHLD\n"},
	{ERR_SIGQUIT, "signal error: failed to catch SIGQUIT\n"},
	{ERR_TSETPGRP, "tcsetpgrp error: "}, {ERR_OK, "Ca marche comme jaja\n"},
};

static size_t g_size = sizeof(g_error) / sizeof(t_numerr);

static int	error(int error)
{
	size_t	i;

	i = -1;
	while (++i < g_size)
	{
		if (g_error[i].num == error)
		{
			printf("%s%s\n", g_error[i].message, strerror(errno));
			break ;
		}
	}
	if (i == g_size)
		printf("Error found not set\n");
	exit(0);
}

static void	sign_handler(int sign)
{
	if (sign == SIGTSTP)
		kill(g_pid, SIGSTOP);
	else if (sign == SIGCHLD)
	{
		if (WIFSTOPPED(g_status))
			printf("Process Son [%d]: Suspended\n", g_pid);
		else if (WIFCONTINUED(g_status))
			printf("Process Son [%d]: Running\n", g_pid);
		else if (!WIFEXITED(g_status))
			printf("Process Son [%d]: Killed\n", g_pid);
		else if (WIFEXITED(g_status))
			printf("Process Son [%d]: Done\n", g_pid);
		else
			printf("Process Son [%d]: Unknown event\n", g_pid);
	}
	else if (sign == SIGQUIT)
	{
		if (tcsetpgrp(0, g_pid) == -1)
			error(ERR_TSETPGRP);
	}
}

int			main(int arc, char **arv, char **env)
{
	pid_t	pid;
	int		i;

	(void)arc;
	(void)arv;
	if ((pid = fork()) == -1)
		error(ERR_FORK);
	else if (!pid)
	{
		if (setpgid(getpid(), 0) == -1)
			error(ERR_SETPGID);
		printf("Pid Son: [%d]\n", getpid());
		i = 4;
		while (i--)
		{
			printf("[%d]scds to press ctrl+%c\n", i, 92);
			sleep(1);
		}
		if (execve("/Users/jraymond/21sh/test/gnl", NULL, env) == -1)
			error(ERR_EXEC);
	}
	else if (pid)
	{
		g_pid = pid;
		if (signal(SIGTSTP, sign_handler) == SIG_ERR)
			error(ERR_SIGTSTP);
		if (signal(SIGQUIT, sign_handler) == SIG_ERR)
			error(ERR_SIGTSTP);
		if (signal(SIGCHLD, sign_handler) == SIG_ERR)
			error(ERR_SIGCHLD);
		if (waitpid(pid, &g_status, WUNTRACED) == -1)
			error(ERR_WAITPID);
		printf("10 scds before ending prog\n");
		sleep(10);
	}
	return (0);
}
