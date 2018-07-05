/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 06:50:53 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/04 19:29:38 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"

static int		opcontext(int ctxt, t_inst *inst, t_ast *nw, t_lexerf *ldef)
{
	size_t	i;
	int		tmpi;

	i = 0;
	tmpi = -1;
	while (i < ldef->ops_len)
	{
		if (ft_strmatch_x(inst->delim, ldef->ops[i].name))
		{
			if ((ldef->ops[i].t & OP_UNARYLR) && (nw->u = (ctxt == 1 ? 1 : -1)))
			{
				nw->u = (ctxt == 1 ? 1 : -1);
				break ;
			}
			else if ((ldef->ops[i].t & OP_UNARYL) && (tmpi = i))
			{
				if ((nw->u = 1) && ctxt == 1)
					break ;
			}
			else if ((ldef->ops[i].t & OP_BINARY) && (tmpi = i))
			{
				if (!(nw->u = 0) && ctxt == 0)
					break ;
			}
		}
		++i;
	}
	if (i == ldef->ops_len && tmpi == -1)
		return (ldef->op_offset - 1);
	nw->assoc = ldef->ops[i == ldef->ops_len ? tmpi : (int)i].t & OP_ASSOCRL;
	return (ldef->op_offset + (i == ldef->ops_len ? tmpi : (int)i));
}

static t_ast	*newast(t_inst *inst, int type, t_lexerf *ldef, t_ast *cur)
{
	t_ast	*nw;

	if (!(nw = ft_memalloc(sizeof(t_ast))))
		return (NULL);
	nw->cmd_offset = ldef->cmd_offset;
	nw->op_offset = ldef->op_offset;
	nw->data = ldef->data;
	if (((nw->type = type)) == ldef->op_offset)
	{
		nw->name = inst->delim;
		if (!inst->args.argv[0])
			type = ((cur && cur->u == -1) ? -1 : 1);
		else
			type = 0;
		nw->type = opcontext(type, inst, nw, ldef) + 1;
	}
	else if ((nw->args = (t_args *)ft_memdup(&inst->args, sizeof(t_args))))
		nw->name = nw->args->argv[0];
	return (nw);
}

static t_ast	*perform_ab(t_ast *dlm, t_ast *cmd, t_ast **head, t_ast *cur)
{
	t_ast	*prev;

	if (head == NULL)
	{
		astlink(cur, dlm, 1);
		return (astlink(dlm, cmd, -1));
	}
	astlink(cur, cmd, 1);
	while ((prev = cur) && cur->parent)
		if (dlm->type < (cur = cur->parent)->type
				|| (dlm->u == -1 && cur->u == 1))
			break ;
	if (prev->parent)
		astlink(prev->parent, dlm, (prev == prev->parent->left ? -1 : 1));
	else
		*head = dlm;
	return (astlink(dlm, prev, -1));
}

static t_ast	*addast0(t_ast *dlm, t_ast *cmd, t_ast **head, t_ast *cur)
{
	if ((!dlm->u && (cur->u == 1 || !cur->u)) || (dlm->u == -1 && !cur->u))
	{
		if (dlm->type < cur->type || (dlm->type == cur->type && dlm->assoc))
			return (perform_ab(dlm, cmd, NULL, cur));
		return (perform_ab(dlm, cmd, head, cur));
	}
	else if (!dlm->u && cur->u == -1 && astlink(cur, cmd, 1))
	{
		if (!cur->parent)
			return (*head = astlink(dlm, cur, -1));
		return (perform_ab(dlm, cmd, head, (cur = cur->parent)));
	}
	else if (dlm->u == 1 || (dlm->u == -1 && cur->u == 1))
		return (perform_ab(dlm, cmd, NULL, cur));
	else if (dlm->u == -1 && cur->u == -1 && astlink(cur, cmd, 1))
	{
		if (!cur->parent && (*head = dlm))
			return (astlink(dlm, cur, -1));
		astlink(cur->parent, dlm,
				(cur == cur->parent->left ? -1 : 1));
		return (astlink(dlm, cur, -1));
	}
	return (cur);
}

static	t_ast	*addast(t_ast **head, t_ast **cur, t_inst *inst, t_lexerf *ldef)
{
	t_ast	*dlm;
	t_ast	*cmd;

	dlm = NULL;
	if (!(cmd = newast(inst, ldef->cmd_offset, ldef, *cur))
		|| (inst->delim && !(dlm = newast(inst, ldef->op_offset, ldef, *cur))))
	{
		astdelone(&cmd);
		ft_argsdel(&inst->args);
		ft_memdel((void **)&inst->delim);
		return (NULL);
	}
	if (!*cur)
	{
		*cur = (dlm ? dlm : cmd);
		*head = (dlm ? dlm : cmd);
		return (dlm ? astlink(dlm, cmd, -1) : dlm);
	}
	if (!dlm && astlink(*cur, cmd, 1))
		return (*cur);
	return (*cur = addast0(dlm, cmd, head, *cur));
}

t_ast			*ft_lexer(const char *str, t_lexerf *ldef)
{
	t_ast	*head;
	t_ast	*cur;
	t_inst	inst;
	int		pos;

	head = NULL;
	cur = NULL;
	ldef->parserf.data = ldef->data;
	while (ft_bzero(&inst, sizeof(t_inst))
			&& (str = ft_parser(str, &inst.args, &ldef->parserf)))
	{
		if (!*str)
			inst.delim = NULL;
		else if ((pos = ft_max(ft_strpbrkstr_len(str, ldef->parserf.def_stop),
				ft_strpbrkstr_len(str, ldef->parserf.def_hstop))))
		{
			inst.delim = ft_strndup(str, pos);
			str += (pos ? pos : 1);
		}
		ft_printf("\t\tAST:\n\n");
		addast(&head, &cur, &inst, ldef);
		ft_astprint(head, 0);
		ft_printf("\n\n");
	}
	return (head);
}
