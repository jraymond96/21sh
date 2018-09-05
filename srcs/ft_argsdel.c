/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argsdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 20:58:56 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/16 19:02:20 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"

void		ft_argsdel(t_args *args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	if (args->argv)
		while (i < args->argc)
			ft_memdel((void **)&args->argv[i++]);
	ft_memdel((void **)&args->argv);
	ft_bzero(args, sizeof(t_args));
}

t_args		*ft_argscopy(t_args *args)
{
	t_args	*nwargs;

	if (!args || !(nwargs = (t_args *)malloc(sizeof(t_args))))
		return (NULL);
	nwargs->argc = args->argc;
	nwargs->argv = ft_copyenv(args->argv);
	return (nwargs);
}
