/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:25:42 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/03 20:35:18 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"
#include <fcntl.h>

static int	shell_exec(int argc, char **argv)
{
	int		script_fd;
	char	*line;

	if (*argv || argc == -1)
	{
		if ((script_fd = (argc == -1 ? 0 : open(*argv, O_RDONLY))) == -1)
			ft_exitf(1, "%s: can't open: %s\n", g_shell->name, *argv);
		get_next_delimstr(script_fd, "\01\02\033EOFEOF\n", &g_shell->script);
		if (script_fd)
			close(script_fd);
	}
	else if (g_shell->history_file)
	{
		if ((script_fd = open(g_shell->history_file,
						O_RDONLY | O_CREAT, 0666)) != -1)
		{
			while (get_next_line(script_fd, &line) >= 0)
			{
				addhistory(line);
				free(line);
			}
			close(script_fd);
		}
	}
	return (0);
}

int			shell_init(int argc, char **argv)
{
	t_opt	opt;

	++argv;
	g_shell->history_file = ".history.log";
	g_shell->start_cmd = "if test -r $HOME/.21shrc then source $HOME/.21shrc";
	while (ft_getopt(&argv, "l.1s.1;log.1", &opt) != OPT_END)
	{
		if (opt.ret == OPT_UNKNOWN)
		{
			if (opt.c == '-')
				ft_exitf(1, "%s: unknown option: %s\n", g_shell->name,
						opt.clong);
			else
				ft_exitf(1, "%s: unknown option: %c\n", g_shell->name, opt.c);
			return (1);
		}
		else if (opt.c == 'l' || (opt.c == '-' && ft_strequ(opt.clong, "log")))
			g_shell->history_file = (opt.ret == OPT_MISSING
					|| ft_strequ(*opt.ptr, "-") ? NULL : *opt.ptr);
		else if (opt.c == 's')
			g_shell->start_cmd = (opt.ret == OPT_MISSING
					|| ft_strequ(*opt.ptr, "-") ? NULL : *opt.ptr);
	}
	(void)argc;
	return (shell_exec((!isatty(0) ? -1 : 1), argv));
}

void		init_gshell(char **envp, char *name)
{
	g_shell->paths = ft_getpaths(envp);
	g_shell->name = name + (*name == '.' ? 2 : 0);
	g_shell->running = 1;
	g_shell->ihis = -1;
	g_shell->exitcode = 0;
}

static void	del_func(void *content, size_t size)
{
	t_func	*func;

	(void)size;
	if ((func = (t_func *)content))
	{
		free(func->name);
		free(func->src);
		ft_astdel(&func->ast);
		free(func);
	}
}

int			shell_end(void)
{
	char	**ptr;
	int		exitcode;

	if ((ptr = g_shell->paths))
		while (*ptr)
			free(*ptr++);
	free(g_shell->paths);
	if ((ptr = g_shell->envp))
		while (*ptr)
			free(*ptr++);
	free(g_shell->script);
	free(g_shell->envp);
	free(g_shell->cline);
	clearhistory(1);
	ft_lstdel(&g_shell->funcs, del_func);
	close(g_shell->ihis);
	exitcode = g_shell->exitcode;
	free(g_shell);
	g_shell = NULL;
	return (exitcode);
}
