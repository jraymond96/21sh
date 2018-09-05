/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_condition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:28:21 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 22:42:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

static int	ast_is(t_ast *ast, char *test)
{
	if (ast && ast->name && ft_strequ(ast->name, test))
		return (1);
	return (0);
}

static int	g_if_failed;

int			shell_else_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_ast	*al;
	int		efail;

	if (ft_strequ(ast->name, "not"))
	{
		if ((efail = ft_astiter(ast->right, res, iterf)))
			return (efail);
		*(int *)res = !*(int *)res;
		return (0);
	}
	if (!(al = ast->left) || !al->name
			|| (ft_strequ(al->name, "then") && !ast_is(al->left, "if")
				&& !ast_is(al->left, "while")))
		return (SH_ELSEWCOND);
	if (!g_if_failed)
	{
		*(int *)res = *(int *)op[0];
		return (0);
	}
	g_if_failed = 0;
	return (ft_astiter(ast->right, res, iterf));
}

static int	while_loop(t_ast *ast, void *res, t_iterf *iterf)
{
	int	ires;
	int	efail;
	int	i;

	i = 0;
	while (!g_shell->kill_builtin)
	{
		*(int *)res = 0;
		ires = 0;
		if ((efail = ft_astiter(ast->left->right, &ires, iterf)))
			return (efail);
		if (ires)
		{
			if (ast_is(ast->left, "if") || (ast_is(ast->left, "while") && !i))
				g_if_failed = 1;
			break ;
		}
		i = 1;
		if ((efail = ft_astiter(ast->right, res, iterf)))
			return (efail);
		if (!ast_is(ast->left, "while"))
			break ;
	}
	return (0);
}

int			shell_cond_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	(void)op;
	g_if_failed = 0;
	if (ft_strequ(ast->name, "if") || ft_strequ(ast->name, "while"))
		return (SH_CONDWTHEN);
	if (!ast_is(ast->left, "if") && !ast_is(ast->left, "while")
			&& !ast_is(ast->parent, "else"))
		return (SH_THENWCOND);
	return (while_loop(ast, res, iterf));
}
