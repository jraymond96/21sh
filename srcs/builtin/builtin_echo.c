/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:27:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/19 14:35:32 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_io.h"

static void	goecho(char **save, char **argv, int ops, char *sep)
{
	char	*l;
	int		fd;

	if (argv != save && ft_strequ(*(argv - 1), "--"))
		--argv;
	fd = (ops & (1 << 2) ? 2 : 1);
	while (*argv)
	{
		l = NULL;
		if (ops & (1 << 1))
			ft_printf_fd(fd, "%.*r", ft_strlenk(*argv),
					(l = ft_strdupk(*argv)));
		else
			ft_putstr_fd(*argv, fd);
		free(l);
		if (*++argv)
			ft_putstr_fd(sep, fd);
	}
	if (!(ops & (1 << 0)))
		ft_putchar_fd('\n', fd);
}

static int	checkerror(t_opt *opt, char ***argv, int ret)
{
	if (opt->seq == 1)
	{
		while (*++opt->cur)
			if (!ft_strchr("rneEc", *opt->cur))
				break ;
		if (*opt->cur && (**argv -= 2))
			return (0);
	}
	else if (opt->cur == NULL && ret == OPT_UNKNOWN)
		return (0);
	else if (ret == OPT_UNKNOWN || ret == OPT_EMPTY)
	{
		--*argv;
		return (0);
	}
	return (1);
}

int			builtin_echo(int argc, char **argv)
{
	t_opt	opt;
	int		ops;
	char	*sep;
	char	**save;

	save = ++argv;
	ops = 0;
	sep = " ";
	while ((argc = ft_getopt(&argv, "rneEc.1", &opt)) != OPT_END)
	{
		if (!checkerror(&opt, &argv, argc))
			break ;
		if (opt.c == 'n')
			ops |= (1 << 0);
		else if (opt.c == 'e')
			ops |= (1 << 1);
		else if (opt.c == 'E')
			ops &= (~(1 << 1));
		else if (opt.c == 'r')
			ops |= (1 << 2);
		else if (opt.c == 'c' && opt.n == 1)
			sep = *opt.ptr;
	}
	goecho(save, argv, ops, sep);
	return (0);
}
