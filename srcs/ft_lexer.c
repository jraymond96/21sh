/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 06:50:53 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/29 17:13:24 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"

static t_ast	*perform_ab(t_ast *dlm, t_ast *cmd, t_ast **head, t_ast *cur)
{
	t_ast	*prev;

	if (head == NULL)
		return (astlink(cur, astlink(dlm, cmd, -1), 1)->right);
	if (cmd)
		astlink(cur, cmd, 1);
	while ((prev = cur) && cur->parent)
	{
		if (dlm->type < (cur = cur->parent)->type
				|| (dlm->u == -1 && cur->u == 1))
			break ;
	}
	if (prev->parent)
		astlink(prev->parent, dlm, (prev == prev->parent->left ? -1 : 1));
	else
	{
		if (dlm->type < prev->type
				&& (prev = prev->right) && astlink(cur, dlm, 1))
			return (astlink(dlm, prev, -1));
		*head = dlm;
	}
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
		astlink(cur, cmd, 1);
		return (perform_ab(dlm, NULL, head, (cur = cur->parent)));
	}
	else if (dlm->u == 2 || dlm->u == 1 || (dlm->u == -1 && cur->u == 1))
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

static	void	addast1(t_inst *inst, t_ast **cur, t_ast **dlm, t_ast **cmd)
{
	if (!*inst->str && *dlm && (*dlm)->u == 2)
	{
		astdelone(cmd);
		ft_swapptr((void **)cmd, (void **)dlm);
		(*cmd)->u = 0;
	}
	if (*cur && (*cur)->u == 2)
	{
		(*cur)->u = 0;
		astdelone(&(*cur)->left);
		astdelone(cmd);
		*cmd = *cur;
		*cur = (*cur)->parent;
	}
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
	addast1(inst, cur, &dlm, &cmd);
	if (!*cur)
	{
		*cur = (dlm ? dlm : cmd);
		*head = (dlm ? dlm : cmd);
		return (dlm ? astlink(dlm, cmd, -1) : dlm);
	}
	if (!dlm)
		return (astlink(*cur, cmd, 1));
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
			&& (pos = ft_parser(&str, &inst.args, &ldef->parserf)) != -1)
	{
		if (!*str)
			inst.delim = NULL;
		else if (pos)
		{
			inst.delim = ft_strndup(str, pos);
			str += (pos ? pos : 1);
		}
		inst.str = (char *)str;
		addast(&head, &cur, &inst, ldef);
	}
	return (head);
}
