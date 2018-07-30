/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:40:15 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 21:53:30 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_list.h"

static void		empty_orderbgproc(pid_t pid)
{
	int	x;

	x = -1;
	while (++x < (MAX_BGPROC - 1) && g_shell->orderbg[x])
		;
	if (x != (MAX_BGPROC - 1))
		g_shell->orderbg[x] = pid;
}


int				nbproc_inbg(t_list *b_list)
{
	int		x;

	x = 0;
	while (b_list && ++x)
		b_list = b_list->next;
	if (x >= MAX_BGPROC)
	{
		ft_printf_fd(2, "21sh: %s (%d)", ft_strchret(SH_MAXBGPROC),
						MAX_BGPROC);
		return (-1);
	}
	else
		return (x);
}

int				handle_bgproc(pid_t  pid_fork, char **cmd)
{
	static int	numproc;
	t_list		*elem;
	t_inffork	*new;

	if (nbproc_inbg(new) == -1)
		return (-1);
	numproc = x == 0 ? 0 : ++numproc;
	if (!(new = init_infproc(numproc, pid_fork, cmd)))
		ft_exitf(EXIT_FAILURE, "21sh: %s\n", ft_strshret(SH_MALLOC));
	ft_lstpush(g_shell->bgproc, new);
	handle_bgstat(pid_fork, BG_RUN);
	return (x);
}
