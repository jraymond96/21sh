/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:16:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 17:30:09 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include <fcntl.h>

static int	end_sig(char *eof, int c, t_ast *ast)
{
	if (eof != ast->right->name)
		free(eof);
	while (c == 3 && ast->parent)
		if (ft_strmatch((ast = ast->parent)->name, "*<<"))
			return (2);
	return (c == 4 || !ast->parent ? 1 : 2);
}

static int	interpret_line(char *line, char *eof, t_expf *expf)
{
	char	*res;

	res = NULL;
	ft_strexpand(line, &res, -1, expf);
	if (res)
		ft_strcpy(line, res);
	free(res);
	if (ft_strequ(line, eof))
		return (1);
	return (0);
}

static int	go_hdoc(t_ast *ast, int fd, t_expf *expf)
{
	char	line[500];
	char	*eof;
	int		c;

	eof = NULL;
	ft_strexpand(ast->right->name, &eof, -1, expf);
	if (!eof)
		eof = ast->right->name;
	while (ft_strclr(line))
	{
		ft_putstr("heredoc> ");
		c = ft_readraw(line, 500);
		ft_putchar('\n');
		if (c == 3 || c == 4)
			return (end_sig(eof, c, ast));
		if (interpret_line(line, eof, expf))
			break ;
		ft_putendl_fd(line, fd);
	}
	if (eof != ast->right->name)
		free(eof);
	return (0);
}

int			shell_hdoc_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	static int	n;
	int			fd;
	int			ret;
	char		*hdoc_file;

	(void)op;
	(void)res;
	*(t_ast **)res = ast;
	if (!ft_astvalid(ast->right))
		return (SH_BADEXPR);
	if (!(hdoc_file = ft_strjoin_clr(HDOC_TMP_FILE, ft_itoa(n++), 1)))
		return (SH_MALLOC);
	if ((fd = open(hdoc_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
		return (SH_OPENFILE);
	if (!(ret = go_hdoc(ast, fd, (t_expf *)iterf->data)))
	{
		ft_strstr(ast->name, "<<")[1] = '\0';
		*ft_memdel((void **)&ast->right->name) = hdoc_file;
		ast->right->args->argv[0] = ast->right->name;
	}
	else
		free(hdoc_file);
	close(fd);
	return (!ret || ret == 2 ? 0 : SH_HDOCSTOP);
}
