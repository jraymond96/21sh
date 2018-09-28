/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstrpv_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 21:20:28 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/18 12:40:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_math.h"
#include "ft_mem.h"

int	g_ifound;

static void	strpbrkstr1(int len, int curs[2], size_t i, t_pair *pos)
{
	if (len)
	{
		if (curs[1] == g_explicitlev)
		{
			if (ft_min(len, curs[0]) == len)
			{
				g_ifound = i;
				if (pos)
					g_ifound /= *(size_t *)pos[1].a;
			}
			curs[0] = ft_min(len, curs[0]);
		}
		else if (g_explicitlev > curs[1])
		{
			curs[1] = g_explicitlev;
			curs[0] = len;
			g_ifound = i;
			if (pos)
				g_ifound /= *(size_t *)pos[1].a;
		}
	}
}

static int	strpbrkstr_type0(const char *a, const char *tab, size_t size,
					t_pair *pos)
{
	int		len;
	int		curs[2];
	size_t	i;

	ft_bzero(curs, sizeof(int) * 2);
	i = 0;
	while (i < size)
	{
		if (*(int *)pos[0].a)
			len = ft_strpbrkstrl_len(a, *(char **)tab + *(size_t *)pos[1].b);
		else
			len = ft_strpbrkstr_len(a, *(char **)tab + *(size_t *)pos[1].b);
		strpbrkstr1(len, curs, i, pos);
		i += *(size_t *)pos[1].a;
		tab += *(size_t *)pos[1].a;
	}
	return (curs[0] ? (g_iread = curs[0]) : curs[0]);
}

static int	strpbrkstr_type1(const char *a, va_list vp, size_t size, int l)
{
	int		len;
	int		curs[2];
	size_t	i;
	char	*str;

	ft_bzero(curs, sizeof(int) * 2);
	i = 0;
	while (i < size)
	{
		str = va_arg(vp, char *);
		if (l)
			len = ft_strpbrkstrl_len(a, str);
		else
			len = ft_strpbrkstr_len(a, str);
		strpbrkstr1(len, curs, i++, NULL);
	}
	return (curs[0] ? (g_iread = curs[0]) : curs[0]);
}

int			ft_strpbrkstrpv_len(const char *a, int type, size_t size,
						va_list vp)
{
	int			ret;
	size_t		as;
	size_t		bs;
	void		*data;
	t_pair		pos[2];

	if (!a)
		return (0);
	ret = 0;
	if (!type)
	{
		data = va_arg(vp, void *);
		as = va_arg(vp, size_t);
		bs = va_arg(vp, size_t);
		pos[0] = ft_make_pair(&ret, NULL);
		pos[1] = ft_make_pair(&as, &bs);
		ret = strpbrkstr_type0(a, data, size, pos);
	}
	else
		ret = strpbrkstr_type1(a, vp, size, ret);
	return (ret);
}

int			ft_strpbrkstrplv_len(const char *a, int type, size_t size,
						va_list vp)
{
	int			ret;
	size_t		as;
	size_t		bs;
	void		*data;
	t_pair		pos[2];

	if (!a)
		return (0);
	ret = 0;
	if (!type)
	{
		data = va_arg(vp, void *);
		as = va_arg(vp, size_t);
		bs = va_arg(vp, size_t);
		pos[0] = ft_make_pair(&ret, NULL);
		pos[1] = ft_make_pair(&as, &bs);
		ret = strpbrkstr_type0(a, data, size, pos);
	}
	else
		ret = strpbrkstr_type1(a, vp, size, ret);
	return (ret);
}
