/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:10:49 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/19 20:56:33 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_types.h"

static t_list	*getrdrctn(t_ast *red)
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
	ptr = red->name + ft_strpbrkstr_pos(red->name, DLM_REDT);
	ptr += ft_strpbrkstr_len(ptr, DLM_REDT);
	r.replace_fd = (*(ptr - 1) == '&' ? 1 : 0);
	if (*ptr == '-')
		r.fd_in = -1;
	else
		r.fd_in = (ft_isdigit(*ptr) ? ft_atoi(ptr) : def);
	r.names = (red->right ? red->right->args : NULL);
	r.str = red->name;
	return (ft_lstnew(&r, sizeof(t_redir)));
}

t_list			*list_redirections(t_ast **ast)
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
			ft_lstpush_p(&lst, getrdrctn(red));
			red = red->parent;
		}
	}
	return (lst);
}
