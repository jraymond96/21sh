/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_astargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 16:36:02 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/30 16:36:07 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ret_args(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast->left)
		ast = ast->left;
	return (ast->args->argv);
}

t_ast	*ret_astargs(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast->left)
		ast = ast->left;
	return (ast);
}
