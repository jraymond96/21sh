/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 21:09:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/26 17:12:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"
#include "ft_str.h"
#include "ft_types.h"

t_func		*get_function(char *name)
{
	t_list	*it;
	t_func	*func;

	it = g_shell->funcs;
	while (it && (func = (t_func *)it->content))
	{
		if (ft_strequ(name, func->name))
			return (func);
		it = it->next;
	}
	return (NULL);
}

static void	shell_equal_cb2(t_ast *astr, char *lstr, t_allf *allf, char *str)
{
	t_func	*funcp;
	t_func	func;

	if (*astr->name == '{')
	{
		if ((funcp = get_function(lstr)))
		{
			free(funcp->name);
			free(funcp->src);
			ft_astdel(&funcp->ast);
		}
		else
			funcp = (t_func *)ft_lstpush_p(&g_shell->funcs,
					ft_lstnew(&func, sizeof(t_func)))->content;
		funcp->name = ft_strdup(lstr);
		funcp->src = ft_strndup(astr->name + 1, ft_strlen(astr->name) - 2);
		funcp->ast = ft_lexer(funcp->src, allf->lexerf);
	}
	else
	{
		ft_strexpand(astr->name, &str, 0, allf->expf);
		ft_setenv(lstr, str, &g_shell->envp);
		free(str);
	}
}

int			shell_equal_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	char	*lstr;
	char	*str;

	(void)op;
	if (!ft_astvalid(ast->left) && (*(int *)res = 1))
		return (SH_BADEXPR);
	lstr = NULL;
	ft_strexpand(ast->left->name, &lstr, 0, ((t_allf *)iterf->data)->expf);
	str = NULL;
	if (!ft_astvalid(ast->right))
		ft_setenv(lstr, "", &g_shell->envp);
	else
		shell_equal_cb2(ast->right, lstr, (t_allf *)iterf->data, str);
	free(lstr);
	*(int *)res = 0;
	return (0);
}

int			check_function(t_ast *ast, void *res, t_iterf *iterf)
{
	t_func	*func;
	t_args	*args;
	int		ret;

	if (!(func = get_function(ast->cname)))
		return (-1);
	args = g_shell->curargs;
	g_shell->curargs = ft_argscopy(ast->cargs);
	ret = ft_astiter(func->ast, res, iterf);
	ft_argsdel(g_shell->curargs);
	free(g_shell->curargs);
	g_shell->curargs = args;
	return (ret);
}
