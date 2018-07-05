/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:30:18 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/24 21:04:29 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_math.h"
#include "ft_printf.h"

int	g_iread;

int	ft_strpbrkstr_len(const char *a, const char *strset)
{
	int		pos;
	int		len;
	int		readmax;
	char	*tmp;

	if (!strset || !a)
		return (0);
	readmax = 0;
	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')))
		{
			++strset;
			continue ;
		}
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (!(tmp = ft_strndup(strset, len + 1)))
			return (0);
		tmp[len] = '*';
		if (ft_strmatch(a, tmp) && ft_memdel((void **)&tmp))
			readmax = ft_max(g_iread, readmax);
		free(tmp);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (readmax);
}

int	ft_strpbrkstrl_len(const char *a, const char *strset)
{
	int		pos;
	int		len;
	int		readmax;
	char	*tmp;

	if (!strset || !a)
		return (0);
	readmax = 0;
	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')))
		{
			++strset;
			continue ;
		}
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (!(tmp = ft_strndup(strset, len + 1)))
			return (0);
		tmp[len] = '*';
		if (ft_strmatchl(a, tmp) && ft_memdel((void **)&tmp))
			readmax = ft_max(g_iread, readmax);
		free(tmp);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (readmax);
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
		{
			if (!a[pos])
				return (-1);
			++pos;
		}
		if (ft_strpbrkstr_len(&a[pos], strset))
			return (pos);
		++pos;
	}
	return (-1);
}
