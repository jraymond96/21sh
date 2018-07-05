/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:25:42 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/04 22:05:05 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_io.h"
#include <fcntl.h>

void	shell_init(int argc, char **argv)
{
	char	*name;
	char	*line;
	char	**ptr;

	(void)argc;
	name = ".history.log";
	g_shell->hisfd = -1;
	if ((ptr = ft_getoptl(++argv, 'l', "log", 1)))
		name = (ft_strequ(*ptr, "-") ? NULL : *ptr);
	if (name)
	{
		if ((g_shell->hisfd = open(name, O_RDONLY | O_CREAT, 0666)) == -1)
			return ;
		while (get_next_line(g_shell->hisfd, &line) >= 0)
		{
			addhistory(line);
			free(line);
		}
		close(g_shell->hisfd);
		g_shell->hisfd = open(name, O_WRONLY, 0666);
	}
}
