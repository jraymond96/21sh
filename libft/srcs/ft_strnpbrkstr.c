/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnpbrkstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 18:32:35 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/08 20:52:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

int	g_iread;

int	ft_strnpbrkstr_len(const char *a, const char *strset, int n)
{
	int		pos;
	int		len;
	char	*tmp;

	while (*strset)
	{
		pos = ft_strchrl_pos(strset, ':');
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (!(tmp = ft_strndup(strset, len + 1)))
			return (0);
		tmp[len] = '*';
		if (ft_strnmatch(a, tmp, n) && ft_memdel((void **)&tmp))
			return (g_iread);
		free(tmp);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (0);
}

int	ft_strnpbrkstrl_len(const char *a, const char *strset, int n)
{
	int		pos;
	int		len;
	char	*tmp;

	while (*strset)
	{
		pos = ft_strchrl_pos(strset, ':');
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (!(tmp = ft_strndup(strset, len + 1)))
			return (0);
		tmp[len] = '*';
		if (ft_strnmatchl(a, tmp, n) && ft_memdel((void **)&tmp))
			return (g_iread);
		free(tmp);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (0);
}

int	ft_strnpbrkstr_pos(const char *a, const char *strset, int n)
{
	int	pos;

	pos = 0;
	while (a[pos] && pos < n)
	{
		if (ft_strnpbrkstr_len(&a[pos], strset, n - pos))
			return (pos);
		++pos;
	}
	return (-1);
}

int	ft_strnpbrkstrl_pos(const char *a, const char *strset, int n)
{
	int	pos;

	pos = 0;
	while (a[pos] && pos < n)
	{
		while (a[pos] == '\\' && ++pos)
		{
			if (!a[pos])
				return (-1);
			++pos;
		}
		if (ft_strnpbrkstrl_len(&a[pos], strset, n - pos))
			return (pos);
		++pos;
	}
	return (-1);
}
