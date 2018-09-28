/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 20:14:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:16:51 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include <fcntl.h>

int	builtin_source(int argc, char **argv)
{
	char	*content;
	int		fd;
	int		res;
	t_ast	*ast;

	if (argc == 1)
	{
		ft_putstr_fd("source: not enough arguments\n", 2);
		return (1);
	}
	else if ((fd = open(argv[1], O_RDONLY)) == -1 && ft_printf_fd(2,
				"source: %s: %s\n", ft_strshret(SH_NEXIST), argv[1]))
		return (1);
	content = NULL;
	get_next_delimstr(fd, "\01\02\033EOFEOF\n", &content);
	close(fd);
	ast = ft_lexer(content, g_shell->allf->lexerf);
	res = 0;
	if ((fd = ft_astiter(ast, &res, g_shell->allf->iterf)) && fd != SH_EXIT)
		ft_printf_fd(2, "%s: %s: [%s]\n", g_shell->name, ft_strshret(fd),
				content);
	ft_astdel(&ast);
	free(content);
	return (res);
}

int	builtin_function(int argc, char **argv)
{
	t_list	*it;
	t_func	*func;
	int		res;
	int		ret;

	it = g_shell->funcs;
	if (argc > 1)
	{
		res = 0;
		++g_shell->curargs->argv;
		--g_shell->curargs->argc;
		if ((func = get_function(argv[1])))
			ret = ft_astiter(func->ast, &res, g_shell->allf->iterf);
		--g_shell->curargs->argv;
		++g_shell->curargs->argc;
		if (!func || ret)
			return (!func ? 127 : 1);
		return (0);
	}
	while (it && (func = (t_func *)it->content))
	{
		ft_printf("[%s]\t\t-> {%s}\n", func->name, func->src);
		it = it->next;
	}
	return (0);
}
