/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 15:27:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/17 15:27:59 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_types.h"
#include "ft_printf.h"

int	builtin_true(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (0);
}

int	builtin_false(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (1);
}

int	builtin_return(int argc, char **argv)
{
	if (argc > 1)
		return ((int)ft_atoui(argv[1]));
	return (g_shell->exitcode);
}
