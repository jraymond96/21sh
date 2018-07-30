/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:30:18 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/10 22:52:35 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"

int	ft_strpbrkstr_len(const char *a, const char *strset)
{
	int		pos;
	int		len;
	int		curs[2];

	if (!strset || !a)
		return (0);
	ft_bzero((void *)curs, sizeof(int) * 2);
	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')) && ++strset)
			continue ;
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (ft_strnmatch_opt(a, strset, len, RGX_END | RGX_N))
		{
			if (curs[1] == g_explicitlev)
				curs[0] = ft_min(g_iread, curs[0]);
			else if (g_explicitlev > curs[1] && (curs[1] = g_explicitlev))
				curs[0] = g_iread;
		}
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	if (curs[0])
		g_iread = curs[0];
	return (curs[0]);
}

int	ft_strpbrkstrl_len(const char *a, const char *strset)
{
	int		pos;
	int		len;
	int		curs[2];

	if (!strset || !a)
		return (0);
	ft_bzero((void *)curs, sizeof(int) * 2);
	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')) && ++strset)
			continue ;
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (ft_strnmatch_opt(a, strset, len, RGX_END | RGX_N | RGX_BKSLSH))
		{
			if (curs[1] == g_explicitlev)
				curs[0] = ft_min(g_iread, curs[0]);
			else if (g_explicitlev > curs[1] && (curs[1] = g_explicitlev))
				curs[0] = g_iread;
		}
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	if (curs[0])
		g_iread = curs[0];
	return (curs[0]);
}

int	ft_strpbrkstr_pos(const char *a, const char *strset)
{
	int	pos;

	if (!strset || !a)
		return (0);
	pos = 0;
	while (a[pos])
	{
		if (ft_strpbrkstr_len(&a[pos], strset))
			return (pos);
		++pos;
	}
	return (-1);
}

int	ft_strpbrkstrl_pos(const char *a, const char *strset)
{
	int	pos;

	if (!strset || !a)
		return (0);
	pos = 0;
	while (a[pos])
	{
		while (a[pos] == '\\' && ++pos)
			if (!a[pos] || !a[++pos])
				return (-1);
		if (ft_strpbrkstr_len(&a[pos], strset))
			return (pos);
		++pos;
	}
	return (-1);
}
