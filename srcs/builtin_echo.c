/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:27:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/16 17:35:07 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_io.h"

static void	goecho(char **argv, int ops, char *sep)
{
	char	*l;

	while (*argv)
	{
		l = NULL;
		if (ops & (1 << 1))
			ft_printf("%.*r", ft_strlenk(*argv), (l = ft_strdupk(*argv)));
		else
			ft_putstr(*argv);
		free(l);
		if (*++argv)
			ft_putstr(sep);
	}
	if (!(ops & (1 << 0)))
		ft_putchar('\n');
}

static int	checkerror(t_opt *opt, char **argv, int ret)
{
	if (opt->seq == 1)
	{
		while (*++opt->cur)
			if (!ft_strchr("neEc", *opt->cur))
				break ;
		if (*opt->cur && (*argv -= 2))
			return (0);
	}
	else if (opt->cur == 0 && ret == OPT_UNKNOWN)
		return (0);
	return (1);
}

int			builtin_echo(int argc, char **argv)
{
	t_opt	opt;
	int		ops;
	char	*sep;

	++argv;
	ops = 0;
	sep = " ";
	while ((argc = ft_getopt(&argv, "neEc.1", &opt)) != OPT_END)
	{
		if (!checkerror(&opt, argv, argc))
			break ;
		if (opt.c == 'n')
			ops |= (1 << 0);
		else if (opt.c == 'e')
			ops |= (1 << 1);
		else if (opt.c == 'E')
			ops &= (~(1 << 1));
		else if (opt.c == 'c' && opt.n == 1)
			sep = *opt.ptr;
	}
	goecho(argv, ops, sep);
	return (0);
}
