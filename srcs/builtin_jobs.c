/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:15:39 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/23 19:26:50 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "shell.h"
#include "ft_types.h"

void	jobs_print(int i)
{
	int	x;

	ft_printf("[%d]%c %s ", g_shell->bgproc[i]->x,
					g_shell->bgproc[i]->sign,
					g_shell->bgproc[i]->status);
	x = -1;
	while (g_shell->bgproc[i]->cmd[++x])
		ft_printf("\t\t%s", g_shell->bgproc[i]->cmd[x]);
	ft_putchar('\n');
}

int		onebg_ask(char **argv)
{
	int	i;
	int	numbg;

	i = -1;
	numbg = ft_atoi(argv[1]);
	while (++i < (MAX_BGPROC - 1) && g_shell->bgproc[i]->x != numbg)
		;
	if (i == (MAX_BGPROC - 1))
	{
		ft_printf("jobs: job not found: %d\n", numbg);
		return (-1);
	}
	else
		jobs_print(i);
	return (0);
}

int		builtin_jobs(int argc, char **argv)
{
	int	i;
	int	numbg;

	i = -1;
	if (argc == 2 && (numbg = ft_atoi(argv[1])))
		return (onebg_ask(argv));
	else
	{
		i = -1;
		while (++i < (MAX_BGPROC - 1))
		{
			if (g_shell->bgproc[i])
				jobs_print(i);
		}
	}
	return (0);
}
