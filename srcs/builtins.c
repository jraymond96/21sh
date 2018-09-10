/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 22:53:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_types.h"

int			builtin_exit(int argc, char **argv)
{
	if (argc > 2 && ft_printf_fd(2, "%s: too many arguments\n", argv[0]))
		return (1);
	else if (argc == 2 && !ft_strforeach(argv[1], ft_isdigit)
			&& ft_printf_fd(2, "%s: numeric argument required\n", argv[0]))
	{
		g_shell->running = 0;
		freelst_bg();
		return (2);
	}
	g_shell->running = 0;
	freelst_bg();
	if (argc == 2)
		return ((int)ft_atoui(argv[1]));
	return (g_shell->exitcode);
}

static int	checkhistory(int clearh)
{
	int		i;
	int		ilen;
	t_list	*it;

	if (clearh)
		clearhistory(0);
	else if ((it = ft_lstend(g_shell->history)))
	{
		ilen = ft_intlen((int)ft_lstsize(g_shell->history));
		i = 0;
		while (it)
		{
			ft_printf("%-*d \t%s\n", ilen, i++, it->content);
			it = it->parent;
		}
	}
	return (0);
}

int			builtin_history(int argc, char **argv)
{
	int		ret;
	int		clr;
	t_opt	opt;

	(void)argc;
	++argv;
	clr = 0;
	while ((ret = ft_getopt(&argv, "c;clear", &opt)) != OPT_END)
	{
		if (ret == OPT_UNKNOWN)
			return (ft_printf("illegal option -- %c\n", opt.c) ? 1 : 1);
		else if (opt.c == 'c'
				|| (opt.c == '-' && ft_strequ(opt.clong, "clear")))
			clr = 1;
	}
	return (checkhistory(clr));
}
