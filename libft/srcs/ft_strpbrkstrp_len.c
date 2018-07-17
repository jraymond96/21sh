/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrkstrp_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:28:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/11 22:38:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_math.h"
#include "ft_mem.h"
#include <stdarg.h>

int	g_ifound;

static void	strpbrkstr1(int len, int curs[2], size_t i, t_pair *pos)
{
	if (len)
	{
		if (curs[1] == g_explicitlev)
		{
			if (ft_min(len, curs[0]) == len)
				g_ifound = i / *(size_t *)pos[1].a;
			curs[0] = ft_min(len, curs[0]);
		}
		else if (g_explicitlev > curs[1])
		{
			curs[1] = g_explicitlev;
			curs[0] = len;
			g_ifound = i / *(size_t *)pos[1].a;
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

int			ft_strpbrkstrp_len(const char *a, const void *data, size_t size,
					...)
{
	va_list		vp;
	int			ret;
	size_t		as;
	size_t		bs;
	t_pair		pos[2];

	if (!a || !data)
		return (0);
	va_start(vp, size);
	as = va_arg(vp, size_t);
	bs = va_arg(vp, size_t);
	va_end(vp);
	ret = 0;
	pos[0] = ft_make_pair(&ret, NULL);
	pos[1] = ft_make_pair(&as, &bs);
	ret = strpbrkstr_type0(a, (const char *)data, size, pos);
	return (ret);
}

int			ft_strpbrkstrpl_len(const char *a, const void *data, size_t size,
						...)
{
	va_list		vp;
	int			ret;
	size_t		as;
	size_t		bs;
	t_pair		pos[2];

	if (!a || !data)
		return (0);
	va_start(vp, size);
	as = va_arg(vp, size_t);
	bs = va_arg(vp, size_t);
	va_end(vp);
	ret = 1;
	pos[0] = ft_make_pair(&ret, NULL);
	pos[1] = ft_make_pair(&as, &bs);
	ret = strpbrkstr_type0(a, (const char *)data, size, pos);
	return (ret);
}
