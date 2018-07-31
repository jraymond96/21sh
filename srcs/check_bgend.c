/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bgend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:04:49 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/31 22:26:41 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_io.h"

static	void	del(void *content, size_t size)
{
	(void)size;
	ft_delenv(&((t_inffork *)content)->cmd);
	ft_memdel(&content);
}

void			print_cmd_args(char **tab)
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

void			print_cmd_args2(char **tab)
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

void			check_bgend(void)
{
	t_list		*elem;
	t_inffork	*struc;

	elem = g_shell->bgproc;
	while (elem)
	{
		struc = elem->content;
		if (end_status(struc->status) != -1)
		{
			if (!*struc->cmd)
				ft_printf("[%d]  %c %s\n", struc->x, struc->sign, 
							struc->status);
			else
				ft_printf("[%d]  %c %s", struc->x, struc->sign,
							struc->status);
			print_cmd_args(struc->cmd);
			ft_lstdelone(&elem, del);
		}
		elem = elem->next;
	}
}
