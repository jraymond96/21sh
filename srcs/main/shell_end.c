/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 23:32:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/20 22:52:25 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	clearhistory(1);
	free(g_shell->history_file);
	ft_lstdel(&g_shell->funcs, del_func);
	exitcode = g_shell->exitcode;
	free(g_shell);
	g_shell = NULL;
	return (exitcode);
}
