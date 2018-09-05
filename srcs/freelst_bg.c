/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelst_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:51:51 by jraymond          #+#    #+#             */
/*   Updated: 2018/08/17 14:52:37 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"

void		del(void *content, size_t size)
{
	(void)size;
	ft_delenv(&((t_inffork *)content)->cmd);
	ft_memdel(&content);
}

void		freelst_bg(void)
{
	t_list	*elem;
	t_list	*next;

	if (!(elem = g_shell->bgproc))
		return ;
	while (elem)
	{
		next = elem->next;
		ft_lstdelone(&elem, del);
		elem = next;
	}
}
