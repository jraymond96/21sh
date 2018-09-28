/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:25:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 19:33:23 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"
#include "ft_mem.h"
#include <fcntl.h>

void		addhistory(char *line)
{
	t_list	*lst;

	if ((g_shell->history && !ft_strcmp(line, g_shell->history->content))
			|| !line[0] || !(lst = ft_lstnew(line, ft_strlen(line) + 1)))
		return ;
	if ((lst->next = ft_lstparent(g_shell->history)))
		lst->next->parent = lst;
	g_shell->history = lst;
}

static void	delhistory(void *content, size_t content_size, void *data)
{
	(void)content_size;
	if (((int *)data)[0] && ((int *)data)[1] != -1)
		ft_putendl_fd((char *)content, ((int *)data)[1]);
	free(content);
}

void		clearhistory(int save)
{
	int	data[2];

	data[0] = save;
	data[1] = open(g_shell->history_file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	g_shell->history = ft_lstend(g_shell->history);
	ft_lstdelv_d(&g_shell->history, delhistory, (void *)data);
	close(data[1]);
}
