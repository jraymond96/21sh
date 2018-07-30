/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deli_shiftend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:21:41 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/25 18:10:57 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		deli_shiftend(int del, int size)
{
	int	x;
	int	y;

	x = 0;
	while (++x < size)
	{
		if (g_shell->orderbg[x] == del)
		{
			g_shell->orderbg[x] = 0;
			break ;
		}
	}
	if ((y = x) == (size - 1))
		return (0);
	while (++x < size && g_shell->orderbg[x])
		g_shell->orderbg[y++] = g_shell->orderbg[x];
	return (0);
}
