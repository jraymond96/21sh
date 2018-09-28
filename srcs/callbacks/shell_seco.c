/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_seco.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 20:16:45 by jraymond          #+#    #+#             */
/*   Updated: 2018/09/24 20:17:01 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				shell_andor_seco_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf)
{
	int	efail;

	if (*ast->name == '|' || *ast->name == '&')
	{
		if ((*ast->name == '|' && *(int *)op[0] != 0)
				|| (*ast->name == '&' && *(int *)op[0] == 0))
			return (ft_astiter(ast->right, res, iterf));
		else
			*(int *)res = *(int *)op[0];
	}
	else if (*ast->name == ';' || *ast->name == ',' || *ast->name == '\n')
	{
		if ((efail = ft_astiter(ast->left, res, iterf)))
			return (efail);
		else if (ast->right && ast->right->name)
			return (ft_astiter(ast->right, res, iterf));
	}
	return (0);
}

int				shell_bckgrnd_cb(t_ast *ast, void **op, void *res,
							t_iterf *iterf)
{
	(void)iterf;
	(void)op;
	if (*ast->name == '&' && exec_cmd_background(ast, res, iterf) != 0)
		return (SH_FORKFAIL);
	return (0);
}
