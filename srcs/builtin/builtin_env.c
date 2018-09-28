/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:27:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 22:47:20 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_io.h"

static int	printusage(t_opt *opt, char **envp)
{
	ft_printf_fd(2, "env: illegal option -- ");
	ft_printf_fd(2, (opt->c == '-' ? "%2$s\n" : "%c\n"), opt->c, opt->clong);
	ft_printf_fd(2, "usage: env [-iv] [-P utilpath] [-u name] "
			"[name=value ...] [utility [argument ...]]\n");
	ft_delenv(&envp);
	return (1);
}

static int	execenv(char **argv, char **envp, char **paths, int verb)
{
	char	fullpath[1024];

	if (*argv)
	{
		if (verb)
		{
			ft_printf("#env executing: %s\n", *argv);
			verb = -1;
			while (argv[++verb])
				ft_printf("#env argv[%d]= \t%s\n", verb, argv[verb]);
		}
		if ((verb = ft_getfullpath(*argv, paths, fullpath, 1024)) != SH_OK
				&& ft_printf_fd(2, "env: %s: %s\n", *argv, ft_strshret(verb)))
			return (127);
		else if (ft_exec(fullpath, argv, envp, NULL) == 126
				&& ft_printf_fd(2, "env: exec format error: %s\n", *argv))
			return (126);
	}
	else if ((paths = envp))
		while (*paths)
			ft_putendl(*paths++);
	return (0);
}

static int	getoptions(char ***argv, char ***envp, char ***paths, int *verb)
{
	t_opt	opt;

	++(*argv);
	while (ft_getopt(argv, "iu.1vP.1", &opt) != OPT_END)
	{
		if (opt.ret == OPT_UNKNOWN)
		{
			printusage(&opt, *envp);
			return (1);
		}
		else if (opt.c == 'u' && opt.ret != OPT_MISSING)
			ft_unsetenv(*opt.ptr, envp);
		else if (opt.c == 'i')
			ft_delenv(envp);
		else if (opt.c == 'v')
			*verb = 1;
		else if (opt.c == 'P' && opt.ret != OPT_MISSING)
			if (!(*paths = ft_strsplit(*opt.ptr, ':')))
				*paths = g_shell->paths;
	}
	return (0);
}

int			builtin_env(int argc, char **argv)
{
	char	**envp;
	char	**paths;

	argc = 0;
	paths = g_shell->paths;
	envp = ft_copyenv(g_shell->envp);
	if (getoptions(&argv, &envp, &paths, &argc))
		return (1);
	while (*argv && ft_strchr(*argv, '='))
		ft_modenv(*argv++, &envp);
	argc = execenv(argv, envp, paths, argc);
	if (paths != g_shell->paths)
		ft_delenv(&paths);
	ft_delenv(&envp);
	return (argc);
}
