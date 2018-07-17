/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:56:07 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/08 19:15:33 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_str.h"
#include "ft_mem.h"

t_list		*ft_strsplit_lst(const char *s, char sep)
{
	t_list	*lsts[3];
	char	*str;
	int		pos;

	if (!s)
		return (NULL);
	ft_bzero(lsts, sizeof(t_list *) * 3);
	while (s)
	{
		pos = ft_strchr_pos(s, sep);
		if (pos != 0 && s[0])
		{
			str = (pos != -1 ? ft_strndup(s, pos) : ft_strdup(s));
			lsts[2] = ft_lstcreate(str, ft_strlen(str) + 1);
			if (lsts[1])
				lsts[1]->next = lsts[2];
			lsts[1] = lsts[2];
			lsts[0] = (!lsts[0] ? lsts[1] : lsts[0]);
		}
		s = (pos != -1 ? s + (pos + 1) : NULL);
	}
	return (lsts[0]);
}

t_list		*ft_strsplitstr_lst(const char *s, const char *sep)
{
	t_list	*lsts[3];
	char	*str;
	size_t	seplen;
	int		pos;

	if (!s || !sep)
		return (NULL);
	seplen = ft_strlen(sep);
	ft_bzero(lsts, sizeof(t_list *) * 3);
	while (s)
	{
		pos = ft_strstr_pos(s, sep);
		if (pos != 0 && s[0])
		{
			str = (pos != -1 ? ft_strndup(s, pos) : ft_strdup(s));
			lsts[2] = ft_lstcreate(str, ft_strlen(str) + 1);
			if (lsts[1])
				lsts[1]->next = lsts[2];
			lsts[1] = lsts[2];
			lsts[0] = (!lsts[0] ? lsts[1] : lsts[0]);
		}
		s = (pos != -1 ? s + (pos + seplen) : NULL);
	}
	return (lsts[0]);
}
