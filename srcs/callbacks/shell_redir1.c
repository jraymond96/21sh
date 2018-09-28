/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 20:53:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 15:24:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"

void	redir_printerror(t_redir *r, int err, void **op)
{
	(void)op;
	ft_printf_fd(2, "%s: %s", g_shell->name, ft_strshret(err));
	if (err == SH_BADFD)
		ft_printf_fd(2, ": %d\n", r->fdb);
	else if (r->file)
		ft_printf_fd(2, ": %s\n", r->file);
	else
		ft_putchar_fd('\n', 2);
}

int		replace_fd(t_redir *r, int *closed_fd)
{
	int	tmp;

	if (r->fdz == -2)
		return (0);
	if (r->fdb == -1)
	{
		close(r->fda);
		*closed_fd |= (1 << (r->fda));
	}
	else if (r->fdb != -1)
	{
		if ((tmp = r->fdz) == r->fdb)
		{
			r->fdz = dup(r->fdz);
			close(tmp);
		}
		if (dup2(r->fdb, r->fda) == -1)
			return (SH_BADFD);
	}
	return (0);
}
