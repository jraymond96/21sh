/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redir_printerror.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:21:37 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 21:10:10 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"

void	shell_redir_printerror(t_redir *r, int err, void **op)
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
