/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:40:15 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/24 20:10:46 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_list.h"
#include "ft_io.h"
#include "ft_mem.h"

static	t_inffork	*init_infproc(int x, pid_t pid, char **cmd)
{
	t_inffork	*new;

	if (!(new = (t_inffork *)ft_memalloc(sizeof(t_inffork))))
		ft_exitf(EXIT_FAILURE, "21sh: %s\n", ft_strshret(SH_MALLOC));
	new->x = x;
	new->pid = pid;
	new->cmd = ft_copyenv(cmd);
	new->sign = ' ';
	return (new);
}

static	t_list		*init_t_list(t_inffork *content, size_t size)
{
	t_list	*elem;

	if (!(elem = (t_list *)ft_memalloc(sizeof(t_list))))
		ft_exitf(EXIT_FAILURE, "21sh: %s\n", ft_strshret(SH_MALLOC));
	elem->content = content;
	elem->content_size = size;
	return (elem);
}

int					nbproc_inbg(t_list *b_list)
{
	int		x;

	x = 0;
	while (b_list && ++x)
		b_list = b_list->next;
	if (x >= MAX_BGPROC)
	{
		ft_printf_fd(2, "21sh: %s (%d)", ft_strshret(SH_MAXBGPROC),
						MAX_BGPROC);
		return (-1);
	}
	return (x);
}

int					handle_bgproc(pid_t pid_fork, char **cmd,
									int status, int opt)
{
	t_list		*elem;
	t_inffork	*new;
	int			ret;

	if ((ret = nbproc_inbg(g_shell->bgproc)) == -1)
		return (-1);
	if (ret == 0)
		g_shell->numproc = 1;
	else
		++g_shell->numproc;
	new = init_infproc(g_shell->numproc, pid_fork, cmd);
	elem = init_t_list(new, sizeof(t_inffork));
	ft_lstpush_p(&g_shell->bgproc, elem);
	if (getpid() != pid_fork && opt)
		handle_bgsign(elem, 0);
	handle_bgstat(pid_fork, status);
	return (0);
}
