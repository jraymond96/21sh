/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:25:42 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/26 15:31:37 by mmerabet         ###   ########.fr       */
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

	if (*argv)
	{
		if ((script_fd = open(*argv, O_RDONLY)) == -1)
			ft_exitf(1, "%s: could not open: %s\n", g_shell->name, *argv);
		get_next_delimstr(script_fd, "\n\n\nEOFEOFEOF\n\n\n", &g_shell->script);
		close(script_fd);
	}
	else if (argc && g_shell->history_file)
	{
		if ((script_fd = open(g_shell->history_file, O_RDONLY | O_CREAT, 0666)) != -1)
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
	while (ft_getopt(&argv, "l.1;log.1", &opt) != OPT_END)
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
		else if (opt.c == 'l' || ft_strequ(opt.clong, "log"))
		{
			if (opt.ret == OPT_MISSING || ft_strequ(*opt.ptr, "-"))
				g_shell->history_file = NULL;
			else
				g_shell->history_file = *opt.ptr;
		}
	}
	return (shell_exec(argc, argv));
}
