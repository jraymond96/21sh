/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 17:21:51 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/26 18:25:41 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <fcntl.h>
#include <sys/wait.h>
#include "../logger/incs/logger.h"

static void	restore_fds(void *c, size_t s)
{
	t_redir	*r;

	(void)s;
	r = (t_redir *)c;
	if (r->checked)
	{
		log_debug("r checked: %d %d %d\n", r->fda, r->fdb, r->fdz);
		if (r->fdb != -1)
		{
			if (r->fdz != -1)
				dup2(r->fdz, r->fda);
			close(r->fdz == -1 ? r->fda : r->fdz);
		}
		else if (r->fdb == -1)
		{
			dup2(r->fdz, r->fda);
			close(r->fdz);
		}
	}
	free(c);
}

static int	replace_fd(t_redir *r, int *closed_fd)
{
	int	tmp;

	tmp = 0;
	r->fdz = dup(r->fda);
	log_debug("replace_fd: %d %d %d\n", r->fda, r->fdb, r->fdz);
	if (r->fdb == -1 && close(r->fda) != -1)
		*closed_fd |= (1 << (r->fda - 1));
	else if (r->fdb != -1)
	{
		if (*closed_fd & (1 << (r->fdb - 1)))
		{
			close(r->fda);
			*closed_fd |= (1 << (r->fda - 1));
		}
		else
		{
			if ((tmp = r->fdz) == r->fdb)
			{
				while ((r->fdz = dup(r->fdz)))
				close(tmp);
			}
			if (dup2(r->fdb, r->fda) == -1)
				return (SH_BADFD);
		}
	}
	return (0);
}

static int	heredoc(t_redir *r)
{
	char	*line;
	int		fd_o;

	if (!r->file)
		return (SH_HDOCWORD);
	fd_o = O_WRONLY | O_TRUNC | O_CREAT;
	if ((fd_o = open("/tmp/.21sh-47965231.hdoc", fd_o, 0666)) == -1)
		return (SH_HDOCWFAIL);
	while (ft_printf("heredoc> ") && get_next_line(0, &line) >= 0)
	{
		if (ft_strequ(line, r->file) && ft_memdel((void **)&line))
			break ;
		ft_printf_fd(fd_o, "%s\n", line);
		ft_memdel((void **)&line);
	}
	close(fd_o);
	fd_o = O_RDONLY | O_CREAT;
	if ((fd_o = open("/tmp/.21sh-47965231.hdoc", fd_o, 0666)) == -1)
		return (SH_HDOCRFAIL);
	r->fdz = dup(r->fda);
	dup2(fd_o, r->fda);
	close(fd_o);
	return (0);
}

static int	dup_file(t_redir *r)
{
	int	fd_o;
	int	fd_k;
	int	bits;

	bits = 0;
	if (!r->file)
		return (SH_BADEXPR);
	if (r->type == TK_LRIGHT)
		bits = (O_APPEND | O_WRONLY | O_CREAT);
	else if (r->type == TK_RIGHT)
		bits = (O_WRONLY | O_TRUNC | O_CREAT);
	else if (r->type == TK_LEFT)
		bits = (O_RDONLY);
	if ((fd_o = open(r->file, bits, 0666)) == -1)
		return (SH_OPENFILE);
	if ((fd_k = fd_o) == r->fda)
	{
		fd_o = dup(fd_o);
		close(fd_k);
	}
	r->fdz = dup(r->fda);
	dup2(fd_o, r->fda);
	close(fd_o);
	return (0);
}

int			shell_redir_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_list	*redirs;
	t_redir	*r;
	t_list	*it;
	int		i[2];

	redirs = list_redirections(&ast, ((t_allf *)iterf->data)->expf);
	it = redirs;
	ft_bzero(i, sizeof(int) * 2);
	while (it && (r = (t_redir *)it->content))
	{
		if ((r->rep && (i[1] = replace_fd(r, &i[0])))
				|| (!r->rep && ((r->type == TK_LLEFT && (i[1] = heredoc(r)))
					|| (r->type != TK_LLEFT && (i[1] = dup_file(r))))))
			break ;
		r->checked = 1;
		it = it->next;
	}
	if (i[1] && i[1] != SH_BADEXPR && (*(int *)res = 1))
		shell_redir_printerror(r, i[1], op);
	else if (!i[1])
		ft_astiter(ast, res, iterf);
	ft_lstdel(&redirs, restore_fds);
	return (i[1] == SH_BADEXPR ? i[1] : 0);
}
