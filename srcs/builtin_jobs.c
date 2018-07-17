/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:15:39 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/16 18:41:22 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "shell.h"
#include "ft_types.h"

int		builtin_jobs(int argc, char **argv)
{
	int	i;
	int	pid;

	i = -1;
	if (argc == 2 && (pid = ft_atoi(argv[1])))
	{
		while (++i < (MAX_BGPROC - 1) && g_shell->bgproc[i]->pid != pid)
			;
		if (i == (MAX_BGPROC - 1))
		{
			ft_printf("jobs: job not found: %d\n", pid);
			return (-1);
		}
		else
		{
			ft_printf("[%d]  %c %s ", g_shell->bgproc[i]->x,
							g_shell->bgproc[i]->sign,
							g_shell->bgproc[i]->status);
		}
	}
	else
	{
		i = -1;
		while (++i < (MAX_BGPROC - 1))
		{
			if (g_shell->bgproc[i])
			{
				ft_printf("[%d]  %c %s ", g_shell->bgproc[i]->x,
							g_shell->bgproc[i]->sign,
							g_shell->bgproc[i]->status);
			}
		}
	}
	return (0);
}
