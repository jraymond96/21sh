/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 22:28:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/17 22:30:36 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"

int			ft_astgood(t_ast *ast)
{
	if (!ast || !ast->left || !ast->left->name || !ast->right
			|| !ast->right->name)
		return (0);
	return (1);
}

void		ft_astprint(t_ast *bt, int n)
{
	int			i;

	if (!bt)
	{
		ft_printf("%?*\tEND\n", n);
		return ;
	}
	ft_printf("%?*\t'%d': '%s'('%s') unary %d\n", n, bt->type, bt->name,
			(bt->parent ? bt->parent->name : NULL), bt->u);
	if (bt->type == bt->cmd_offset && bt->args && bt->args->argc > 1)
	{
		i = -1;
		ft_printf("%?*\tArgs: \n", n + 1);
		while (++i < bt->args->argc)
			ft_printf("%?*\t '%s'\n", n + 1, bt->args->argv[i]);
	}
	ft_printf("%?*\tLeft {\n", n);
	ft_astprint(bt->left, n + 1);
	ft_printf("%?*\t}\n%1$?*\tRight {\n", n);
	ft_astprint(bt->right, n + 1);
	ft_printf("%?*\t}\n", n);
}

int			ft_astvalid(t_ast *ast)
{
	if (!ast || !ast->name)
		return (0);
	return (1);
}
