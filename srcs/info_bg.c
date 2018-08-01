/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:40:15 by jraymond          #+#    #+#             */
/*   Updated: 2018/08/01 18:10:23 by jraymond         ###   ########.fr       */
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

	if (!(elem = (t_list *)malloc(size)))
		ft_exitf(EXIT_FAILURE, "21sh: %s\n", ft_strshret(SH_MALLOC));
	elem->content = content;
	elem->content_size = size;
	elem->next = NULL;
	elem->parent = NULL;
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
	else
		return (x);
}

int					handle_bgproc(pid_t  pid_fork, char **cmd, int status)
{
	static int	numproc;
	t_list		*elem;
	t_inffork	*new;
	int			ret;

	if ((ret = nbproc_inbg(g_shell->bgproc)) == -1)
		return (-1);
	numproc = ret == 0 ? 1 : ++numproc;
	new = init_infproc(numproc, pid_fork, cmd);
	elem = init_t_list(new, sizeof(t_inffork));
	if (!g_shell->bgproc)
		g_shell->bgproc = elem;
	else
		ft_lstpush(g_shell->bgproc, elem);
	handle_bgsign(elem, 0);
	handle_bgstat(pid_fork, status);
	return (0);
}
