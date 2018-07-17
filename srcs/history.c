/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:25:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/04 21:01:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"
#include "ft_mem.h"

t_shell	*g_shell;

void		addhistory(char *line)
{
	t_list	*lst;

	g_shell->ihis = -1;
	free(g_shell->cline);
	g_shell->cline = NULL;
	if ((g_shell->history && !ft_strcmp(line, g_shell->history->content))
			|| !line[0] || !(lst = ft_lstnew(line, ft_strlen(line) + 1)))
		return ;
	if ((lst->next = ft_lstparent(g_shell->history)))
		lst->next->parent = lst;
	g_shell->history = lst;
}

char		*gethistory(int i)
{
	t_list	*lst;

	if (i == -1 && g_shell->cline)
		return (g_shell->cline);
	else if ((lst = ft_lstatpos(g_shell->history, i)))
		return ((char *)lst->content);
	return ("");
}

static void	delhistory(void *content, size_t content_size, void *data)
{
	(void)content_size;
	if (*(int *)data && g_shell->hisfd != -1)
		ft_putendl_fd((char *)content, g_shell->hisfd);
	free(content);
}

void		clearhistory(int save)
{
	g_shell->history = ft_lstend(g_shell->history);
	ft_lstdelv_d(&g_shell->history, delhistory, &save);
}

void		movehistory(char c, char *line, size_t *cursor)
{
	char	*str;
	char	*tmp;

	if (*cursor > 0)
		ft_printf("\033[%dD\033[K", *cursor);
	if (g_shell->ihis == -1)
		g_shell->cline = ft_strdup(line);
	ft_strclr(line);
	if (c == 'A' && g_shell->ihis < (int)ft_lstsize(g_shell->history) - 1)
		++g_shell->ihis;
	else if (c == 'B' && g_shell->ihis > -1)
		--g_shell->ihis;
	ft_strcpy(line, (str = gethistory(g_shell->ihis)));
	ft_putstr((tmp = ft_strrep(line, '\t', ' ')));
	free(tmp);
	if (str == g_shell->cline)
		ft_memdel((void **)&g_shell->cline);
	*cursor = ft_strlen(line);
}
