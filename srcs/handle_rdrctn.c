/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:10:49 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/25 17:09:53 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"
#include "ft_mem.h"
#include "ft_printf.h"

static t_list	*implement_args(t_ast *cmd, t_ast *red, t_redir *r,
							t_expf *expf)
{
	char	**ptr;
	char	*s;
	t_args	*args;
	t_ast	*right;

	r->names = NULL;
	r->file = NULL;
	r->str = red->name;
	if (!(right = red->right))
		return (ft_lstnew(r, sizeof(t_redir)));
	ft_astcresolver(right, expf);
	r->names = right->cargs;
	r->file = (right->cargs->argv ? right->cargs->argv[0] : NULL);
	if (right->args && (ptr = right->args->argv) && right->args->argc > 1)
	{
		args = cmd->args;
		while (*++ptr && (s = ft_strdup(*ptr)))
			args->argv = ft_memjoin_clr(args->argv,
				sizeof(char *) * args->argc++, &s, sizeof(char *));
		args->argv = ft_memjoin_clr(args->argv,
			sizeof(char *) * args->argc, ptr, sizeof(char *));
	}
	return (ft_lstnew(r, sizeof(t_redir)));
}

static t_list	*getrdrctn(t_ast *red, t_ast *cmd, t_expf *expf)
{
	t_redir		r;
	char		*ptr;
	int			def;

	if (ft_strmatch(red->name, "*>>*"))
		r.type = TK_LRIGHT;
	else if (ft_strmatch(red->name, "*<<*"))
		r.type = TK_LLEFT;
	else if (ft_strmatch(red->name, "*>*"))
		r.type = TK_RIGHT;
	else if (ft_strmatch(red->name, "*<*"))
		r.type = TK_LEFT;
	def = (r.type == TK_LEFT || r.type == TK_LLEFT ? 0 : 1);
	r.fd_out = (ft_isdigit(*red->name) ? ft_atoi(red->name) : def);
	ptr = red->name;
	while (ft_isdigit(*ptr))
		++ptr;
	ptr += ((r.type == TK_LLEFT || r.type == TK_LRIGHT) ? 2 : 1);
	r.replace_fd = (*ptr == '&' ? 1 : 0);
	if (r.replace_fd && *(ptr + 1) == '-')
		r.fd_in = -1;
	else if (r.replace_fd)
		r.fd_in = (ft_isdigit(*(ptr + 1)) ? ft_atoi(ptr + 1) : def);
	return (implement_args(cmd, red, &r, expf));
}

t_list			*list_redirections(t_ast **ast, t_expf *expf)
{
	t_list	*lst;
	t_ast	*red;
	t_ast	*parent;

	lst = NULL;
	if (ast && *ast && (*ast)->type == TK_REDIR)
	{
		parent = (*ast)->parent;
		while ((*ast)->left)
			*ast = (*ast)->left;
		red = (*ast)->parent;
		while (red != parent)
		{
			ft_lstpush_p(&lst, getrdrctn(red, *ast, expf));
			red = red->parent;
		}
	}
	return (lst);
}
