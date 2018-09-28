/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:35:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/12 22:38:51 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"

static int		getlen(const char *s, int t, t_mchi *mchi)
{
	if ((t = ft_strnchrl_pos(s, '@', (size_t)t)) != -1)
	{
		mchi->whatever = 0;
		if (t == 1)
			mchi->type = 1;
		if (s[t + 1] == '<' || s[t + 1] == '>')
			mchi->t = (s[t + 1] == '<' ? 2 : 3);
		else if (s[t + 1] == '=')
			mchi->t = 1;
		else if (s[t + 1] == 'b')
			mchi->type = 3;
		else
		{
			mchi->len = (ft_isdigit(s[t + 1]) ? (int)ft_atoui(&s[t + 1]) : -1);
			return (t);
		}
		mchi->len = (ft_isdigit(s[t + 2]) ? (int)ft_atoui(s + (t + 2)) : -1);
		return (t);
	}
	return (-1);
}

static t_mchi	*newmchi(const char **s, int len, int t)
{
	t_mchi	*mchi;

	if (!(mchi = ft_memalloc(sizeof(t_mchi))))
		return (NULL);
	if (!t && (mchi->str = ft_strndupl(*s, len)))
		mchi->level = ft_strlen(mchi->str);
	else if (t)
	{
		mchi->type = 1;
		mchi->len = -1;
		mchi->whatever = 1;
		*s += len;
		if (**s == '[' && (len = ft_strpbrkl_pos(*s, "]")) != -1)
		{
			mchi->whatever = 0;
			mchi->type = 2;
			t = getlen(*s, len, mchi);
			if (!*(mchi->str =
						ft_strndup(*s + 1, (size_t)((t == -1 ? len : t) - 1))))
				mchi->type = 1;
			*s += len + 1;
		}
		mchi->level = (mchi->type == 3 ? 2 : 1);
	}
	return (mchi);
}

static t_mchi	*addmchi(t_mchi **head, t_mchi *nw)
{
	t_mchi	*tail;

	if (!(tail = *head))
		return (*head = nw);
	(*head)->level += nw->level;
	while (tail->next)
		tail = tail->next;
	tail->whatever = 0;
	return (tail->next = nw);
}

int				g_explicitlev;

t_mchi			*ft_getmchi(const char *match)
{
	t_mchi		*head;
	int			pos;
	int			len;

	head = NULL;
	while (*match)
	{
		if ((pos = ft_strpbrkl_pos(match, "*")) == -1)
			len = ft_strlen(match);
		else
			len = pos;
		if (len > 0)
			addmchi(&head, newmchi(&match, len, 0));
		if (pos != -1)
			addmchi(&head, newmchi(&match, ++len, 1));
		else
			match += len;
	}
	g_explicitlev = head->level;
	return (head);
}

void			ft_delmchi(t_mchi *head)
{
	t_mchi	*tmp;

	while (head)
	{
		tmp = head->next;
		ft_memdel((void **)&head->str);
		ft_memdel((void **)&head);
		head = tmp;
	}
}
