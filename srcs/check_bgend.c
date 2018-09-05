/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bgend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:04:49 by jraymond          #+#    #+#             */
/*   Updated: 2018/08/17 14:48:30 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_io.h"

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

t_list			*delete_info(t_list *elem)
{
	int		i;
	t_list	*save;

	i = -1;
	save = elem->next;
	ft_lstextract(&g_shell->bgproc, elem);
	ft_lstdelone(&elem, del);
	if (i == 0)
		return (g_shell->bgproc);
	else
		return (save);
}

t_list			*check_bgend_bis(t_inffork *struc, t_list *elem)
{
	if (!*struc->cmd)
		ft_printf("[%d]  %c %s\n", struc->x, struc->sign,
					struc->status);
	else
		ft_printf("[%d]  %c %s", struc->x, struc->sign,
					struc->status);
	print_cmd_args(struc->cmd);
	struc->modif &= (0 << 0);
	return (elem->next);
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
			handle_bgsign(elem, 1);
			elem = delete_info(elem);
		}
		else if (struc->modif & (1 << 0))
			elem = check_bgend_bis(struc, elem);
		else
			elem = elem->next;
	}
}
