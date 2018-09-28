/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_expansions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 14:52:54 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/14 16:45:20 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include <sys/wait.h>
#include <fcntl.h>

static int		exp_cmd2(int fd[2], char **res)
{
	char	*line;
	char	*all;

	wait(NULL);
	close(fd[1]);
	all = NULL;
	while (get_next_line(fd[0], &line) >= 0)
	{
		if (all)
			all = ft_strjoinc_clr(all, '\n');
		all = ft_strjoin_clr(all, line, 2);
	}
	*res = all;
	close(fd[0]);
	return (0);
}

static t_ast	*lexer_iter(char *str, t_expf *ef, int *efail)
{
	t_ast	*ast;

	str += (*str == '$' ? 2 : 1);
	ast = ft_lexer(str, ((t_allf *)ef->data)->lexerf);
	if ((*efail = ft_astiter(ast, efail, ((t_allf *)ef->data)->iterf)))
		ft_printf_fd(2, "%s: error in command substitution: %s: [%s]\n",
			g_shell->name, ft_strshret(*efail), str);
	return (ast);
}

int				exp_cmd(t_strid *sid, char **res, t_expf *expf)
{
	int		fd[2];
	int		efail;
	t_ast	*head;
	pid_t	pid;
	pid_t	save;

	save = getpgrp();
	if (pipe(fd) == -1)
		return (SH_PIPFAIL);
	if ((pid = fork()) == -1 && !close(fd[0]) && !close(fd[1]))
		return (SH_FORKFAIL);
	else if (!pid && !(sid->str[sid->len - 1] = '\0') && !close(fd[0]))
	{
		dup2(fd[1], 1);
		handle_pgid();
		head = lexer_iter(sid->str, expf, &efail);
		ft_astdel(&head);
		tcsetpgrp(0, save);
		close(fd[1]);
		exit(efail ? 1 : 0);
	}
	return (exp_cmd2(fd, res));
}

int				exp_dvar(t_strid *sid, char **res, t_expf *expf)
{
	char	*str;
	char	*final;
	char	*ores;
	int		efail;

	str = sid->str + 2;
	ores = NULL;
	sid->str[sid->len - 1] = '\0';
	efail = ft_strexpand(str, &ores, 0, expf);
	sid->str[sid->len - 1] = '}';
	if (efail)
		return (efail);
	final = ft_strnew(ft_strlen(ores) + 1);
	ft_strcpy(final + 1, ores);
	final[0] = '$';
	free(ores);
	*res = NULL;
	efail = ft_strexpand(final, res, sid->j, expf);
	free(final);
	return (efail);
}
