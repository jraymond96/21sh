/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:03:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/20 19:49:17 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_io.h"
#include <unistd.h>

static int	lorp(char ***argv)
{
	int		lp;
	t_opt	opt;

	lp = 1;
	ft_bzero(&opt, sizeof(t_opt));
	++(*argv);
	while (ft_getopt(argv, "LP", &opt) != OPT_END)
	{
		if (opt.c == 'L')
			lp = 1;
		else if (opt.c == 'P')
			lp = 0;
		else if (opt.c == '\0' && (*argv = opt.ptr - 1))
			break ;
		else if (ft_printf_fd(2, "cd: bad option: %c\n", opt.c))
			return (-1);
	}
	return (lp);
}

static int	goto_home(char *name)
{
	int	acc;

	if (!g_shell->homepwd)
	{
		ft_printf_fd(2, "%s: HOME not set\n", name);
		return (1);
	}
	if ((acc = ft_chdirl(g_shell->homepwd, g_shell->pwd, 2048)) == SH_OK)
	{
		ft_setenv("OLDPWD", ft_getenv("PWD", g_shell->envp), &g_shell->envp);
		ft_setenv("PWD", g_shell->pwd, &g_shell->envp);
		return (0);
	}
	ft_printf_fd(2, "%s: %s: %s\n", name, ft_strshret(acc), g_shell->homepwd);
	return (1);
}

int			builtin_cd(int argc, char **argv)
{
	int		acc;
	char	*name;

	name = NULL;
	if (argc == 1)
		return (goto_home(argv[0]));
	else if (argc > 1)
	{
		if ((argc = lorp(&argv)) == -1)
			return (1);
		if (ft_strequ((name = argv[0]), "-"))
			name = ft_getenv("OLDPWD", g_shell->envp);
		if ((acc = ft_chdir(name, g_shell->pwd, 2048, argc)) != SH_OK)
			return (!!ft_printf_fd(2, "cd: %s: %s\n", ft_strshret(acc), name));
		if (ft_strequ(argv[0], "-") && name)
			ft_printf("%s\n", name);
		else if (ft_strequ(argv[0], "-"))
			return (!!ft_printf_fd(2, "cd: OLDPWD not set\n"));
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", g_shell->envp), &g_shell->envp);
	ft_setenv("PWD", g_shell->pwd, &g_shell->envp);
	return (0);
}

static void	print_pwd(int h)
{
	int		len;

	if (h)
	{
		len = (int)ft_strlen(g_shell->homepwd);
		if (ft_strnequ(g_shell->pwd, g_shell->homepwd, len))
		{
			ft_putchar('~');
			ft_putstr(g_shell->pwd + len);
			return ;
		}
	}
	ft_putstr(g_shell->pwd);
}

int			builtin_pwd(int argc, char **argv)
{
	t_opt	opt;

	argc = 0;
	ft_bzero(&opt, sizeof(t_opt));
	++argv;
	while (ft_getopt(&argv, "LPnh", &opt) != OPT_END)
	{
		if (opt.c == 'L')
			argc &= (~(1 << 0));
		else if (opt.c == 'P')
			argc |= (1 << 0);
		else if (opt.c == 'n')
			argc |= (1 << 1);
		else if (opt.c == 'h')
			argc |= (1 << 2);
		else if (ft_printf_fd(2, "pwd: bad option: %c\n", opt.c))
			return (1);
	}
	if (argc & (1 << 0))
		ft_printf("%s", ft_getcwd(NULL, 0));
	else
		print_pwd((argc & (1 << 2)));
	if (!(argc & (1 << 1)))
		ft_printf("\n");
	return (0);
}
