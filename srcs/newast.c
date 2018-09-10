/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newast.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 01:28:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/18 21:49:32 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"

static int	beyond_norm(int ctxt, t_ast *nw, int *set_tmpi, int t)
{
	if ((t & OP_UNARYLR) && (nw->u = (ctxt == 1 ? 1 : -1)))
		return (1);
	else if ((t & OP_UNARYL) && (*set_tmpi = 1))
	{
		if ((nw->u = 1) && ctxt == 1)
			return (1);
	}
	else if ((t & OP_BINARY) && (*set_tmpi = 1))
	{
		if (!(nw->u = 0) && ctxt == 0)
			return (1);
	}
	else if (t & OP_UNARYRM)
	{
		nw->u = 2;
		if (ctxt == 0 || (nw->parent && (nw->parent->u == -1
						|| nw->parent->u == 2)))
			nw->u = -1;
		return (1);
	}
	return (0);
}

static int	opcontext(int ctxt, t_inst *inst, t_ast *nw, t_lexerf *ldef)
{
	size_t	i;
	int		tmpi;
	int		set_tmpi;

	i = 0;
	tmpi = -1;
	while (i < ldef->ops_len)
	{
		if (ft_strmatch_x(inst->delim, ldef->ops[i].name))
		{
			set_tmpi = 0;
			if (beyond_norm(ctxt, nw, &set_tmpi, ldef->ops[i].t))
				break ;
			if (set_tmpi)
				tmpi = i;
		}
		++i;
	}
	if (i == ldef->ops_len && tmpi == -1)
		return (ldef->op_offset - 1);
	nw->assoc = ldef->ops[i == ldef->ops_len ? tmpi : (int)i].t & OP_ASSOCRL;
	return (ldef->op_offset + (i == ldef->ops_len ? tmpi : (int)i));
}

t_ast		*newast(t_inst *inst, int type, t_lexerf *ldef, t_ast *cur)
{
	t_ast	*nw;

	if (!(nw = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	nw->cmd_offset = ldef->cmd_offset;
	nw->op_offset = ldef->op_offset;
	nw->data = ldef->data;
	nw->lexerf = ldef;
	if (((nw->type = type)) == ldef->op_offset)
	{
		nw->name = inst->delim;
		type = 0;
		if (!inst->args.argv[0])
			type = ((cur && (cur->u == -1 || cur->u == 2)) ? -1 : 1);
		nw->parent = cur;
		nw->type = opcontext(type, inst, nw, ldef) + 1;
		if (nw->u == 2)
			nw->type = ldef->cmd_offset;
		nw->parent = NULL;
	}
	else if ((nw->args = (t_args *)ft_memdup(&inst->args, sizeof(t_args))))
		nw->name = nw->args->argv[0];
	return (nw);
}
