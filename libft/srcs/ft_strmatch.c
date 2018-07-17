/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 16:10:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/08 17:51:56 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

int	ft_strmatchl(const char *str, const char *match)
{
/*	char	*strl;
	int		ret;
	int		i;

	if (!str || !match || !(strl = ft_strdupli(str)))
		return (0);
	ret = ft_strmatch(strl, match);
	if (ret)
	{
		i = 0;
		while (i < g_iread)
		{
			if (str[i] == '\\')
			{
				if (str[++i])
					++g_iread;
				++g_iread;
			}
			++i;
		}
	}
	free(strl);
	return (ret);*/
	return (ft_strmatch_opt(str, match, RGX_BKSLSH));
}

int	ft_strnmatchl(const char *str, const char *match, int n)
{
/*	char	*strl;
	int		ret;
	int		i;

	if (!str || !match || !(strl = ft_strdupli(str)))
		return (0);
	ret = ft_strnmatch(strl, match, n);
	if (ret)
	{
		i = 0;
		while (i < g_iread)
		{
			if (str[i] == '\\')
			{
				if (str[++i])
					++g_iread;
				++g_iread;
			}
			++i;
		}
	}
	free(strl);
	return (ret);*/
	return (ft_strnmatch_opt(str, match, n, RGX_BKSLSH));
}

int	ft_strmatch(const char *str, const char *match)
{
/*	int		ret;
	t_mchi	*head;

	if (!str || !match || !(head = ft_getmchi(match)))
		return (0);
	ret = ft_strtks(str, head, 0);
	ft_delmchi(head);
	return (ret);*/
	return (ft_strmatch_opt(str, match, 0));
}

int	ft_strnmatch(const char *str, const char *match, int n)
{
/*	int		ret;
	t_mchi	*head;

	if (!str || !match || !(head = ft_getmchi(match)))
		return (0);
	ret = ft_strntks(str, head, n, 0);
	ft_delmchi(head);
	return (ret);*/
	return (ft_strnmatch_opt(str, match, n, 0));
}

int	ft_strmatch_x(const char *a, const char *strset)
{
	int		pos;
	int		len;
	char	*tmp;

	if (!strset || !a)
		return (0);
	while (*strset)
	{
		if (!(pos = ft_strchrl_pos(strset, ':')))
		{
			++strset;
			continue ;
		}
		len = (pos == -1 ? (int)ft_strlen(strset) : pos);
		if (!(tmp = ft_strndup(strset, len)))
			return (0);
		if (ft_strmatch(a, tmp) && ft_memdel((void **)&tmp))
			return (g_iread);
		ft_memdel((void **)&tmp);
		strset += (pos == -1 ? ft_strlen(strset) : (size_t)(pos + 1));
	}
	return (0);
}
