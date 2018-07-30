/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bgend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:04:49 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 16:56:44 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_io.h"

void	print_cmd_args(char **tab)
{
	int	x;

	x = -1;
	if (!tab || !tab[0])
		return ;
	while (tab[++x] && tab[x + 1])
		ft_printf(" %s", tab[x]);
	if (x && tab[x])
		ft_printf("%s\n", tab[x]);
	else if (tab[x])
		ft_printf(" %s\n", tab[x]);
}

void	print_cmd_args2(char **tab)
{
	int	x;

	x = -1;
	if (!tab || !tab[0])
		return ;
	while (tab[++x] && tab[x + 1])
		ft_printf(" %s", tab[x]);
	if (!x && tab[x])
		ft_printf("%s\n", tab[x]);
	else if (tab[x])
		ft_printf("%s\n", tab[x]);
}

void					check_bgend(void)
{
	size_t	x;

	x = -1;
	while (++x < (MAX_BGPROC - 1))
	{
		if (g_shell->bgproc[x] && end_status(g_shell->bgproc[x]->status) != -1)
		{
			if (!*g_shell->bgproc[x]->cmd)
				ft_printf("[%d]  %c %s\n", g_shell->bgproc[x]->x,
							g_shell->bgproc[x]->sign,
							g_shell->bgproc[x]->status);
			else
				ft_printf("[%d]  %c %s", g_shell->bgproc[x]->x,
							g_shell->bgproc[x]->sign,
							g_shell->bgproc[x]->status);
			print_cmd_args(g_shell->bgproc[x]->cmd);
			ft_delenv(&g_shell->bgproc[x]->cmd);
			ft_memdel((void **)&g_shell->bgproc[x]);
		}
	}
}
