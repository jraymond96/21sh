/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:37:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/06 15:20:44 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

static int	chunkresolver(char *str[2], int j, int ig, t_args *args)
{
	int		i;
	int		n[3];

	n[1] = j;
	n[2] = ig;
	if ((n[0] = ft_strpbrkstrl_len(str[0], args->exp_all)))
	{
		i = -1;
		while (args->exps && ++i < (int)args->exps_len)
			if (ft_strpbrkstr_len(str[0], args->exps[i].name))
				break;
		if (i == (int)args->exps_len || !args->exps[i].func)
			str[1] = ft_strndup(str[0], n[0]);
		else if ((i = args->exps[i].func(str[0], n, args->data, &str[1])))
			return (i);
		if (str[1] == str[0])
			str[1] = ft_strndup(str[0], n[0]);
		str[0] += n[0];
		return (0);
	}
	if ((n[0] = ft_strpbrkstrl_pos(str[0], args->exp_all)) == -1)
		n[0] = (int)ft_strlen(str[0]);
	str[1] = ft_strndup(str[0], n[0]);
	str[0] += n[0];
	return (0);
}

int		ft_resolver(t_args *args, int onlyfirst)
{
	int		is[3];
	char	*str[2];
	char	*final;

	if (!args || !args->argv)
		return (0);
	is[0] = -1;
	while (++is[0] < args->argc && ((onlyfirst && is[0] == 0) || !onlyfirst))
	{
		is[1] = -1;
		final = NULL;
		str[0] = args->argv[is[0]];
		while (*str[0] && ((onlyfirst && is[1] <= 0) || !onlyfirst))
		{
			str[1] = NULL;
			if ((is[2] = chunkresolver(str, ++is[1], is[0], args))
					&& ft_memdel_x(2, (void **)&final, (void **)&str[1]))
				return (is[2]);
			final = ft_strjoin_clr(final, str[1], 2);
		}
		if (final)
			free(args->argv[is[0]]);
		args->argv[is[0]] = (final ? final : args->argv[is[0]]);
	}
	return (0);
}

int		ft_astresolver(t_ast *ast, int onlyfirst)
{
	int	efail;

	if (!ast || !ast->args || !ast->args->argv)
		return (0);
	if ((efail = ft_resolver(ast->args, onlyfirst)))
		return (efail);
	ast->name = ast->args->argv[0];
	return (0);
}
