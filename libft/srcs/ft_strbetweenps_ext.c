/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbetweenps_ext.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:09:34 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/05 16:52:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static int	checkbet(char **s, t_pairint *pi)
{
	char	atmp;
	char	btmp;
	int		ret;
	char	bstr[1024];

	if ((atmp = pi->a[pi->la]) == '?' && ft_bzero(bstr, 1024))
	{
		ft_strcatc(ft_strncat(bstr, pi->a, pi->len), ';');
		ft_strncat(bstr, pi->ext, pi->a - pi->ext - (pi->a[pi->len] ? 0 : 1));
		ft_strcat(bstr, pi->a + pi->len + (pi->a[pi->len] ? 1 : 0));
		if ((ret = ft_strbetweenps_ext(s, bstr)) == -1)
			return (-1);
		*s += ret;
		return (0);
	}
	btmp = pi->b[pi->lb];
	pi->a[pi->la] = '\0';
	pi->b[pi->lb] = '\0';
	if ((ret = ft_strbetweenps(s, pi->a, pi->b)) != -1)
		*s += ret;
	pi->a[pi->la] = atmp;
	pi->b[pi->lb] = btmp;
	return (ret);
}

static int	checkequ(char **s, int f, t_pairint *pi, int r)
{
	if ((pi->la = ft_strnpbrkl_pos(pi->a, "*?", pi->len)) == -1)
	{
		pi->lb = pi->len;
		pi->la = pi->len;
		pi->b = pi->a;
	}
	else
	{
		pi->b = pi->a + pi->la + 1;
		pi->lb = pi->len - pi->la - 1;
	}
	if (f && r > 0 && pi->la == pi->lb && ft_strnequl(pi->a, pi->b, pi->la)
			&& ft_strnequl(*s, pi->b, pi->lb) && (*s += pi->lb))
		return (1);
	if (f && ft_strnequl(*s, pi->a, pi->la) && (*s += pi->la))
		return (2);
	else if (f && ft_strnequl(*s, pi->b, pi->lb) && (*s += pi->lb))
		return (1);
	else if (!f && ft_strnequl(*s, pi->a, pi->la))
		return (checkbet(s, pi));
	return (-1);
}

static int	checkext(char **s, char *ext, t_pairint *pi, int r)
{
	int		seco;
	int		f;

	f = 1;
	pi->ext = ext;
	while (*ext)
	{
		if (!r && !f)
			return (-1);
		pi->a = ext;
		seco = ft_strchrl_pos(ext, ';');
		if ((pi->len = (seco == -1 ? (int)ft_strlen(ext) : seco)) == 0)
		{
			ext += 1;
			break ;
		}
		if ((f = checkequ(s, f, pi, r)) != -1)
			return (f);
		ext += (seco == -1 ? pi->len : pi->len + 1);
		f = 0;
	}
	return (-1);
}

int			ft_strbetweenps_ext(char **s, const char *ext)
{
	char		*it;
	int			ret;
	int			r;
	t_pairint	pi;

	if (!s || !*s || !ext)
		return (-1);
	it = *s;
	r = 0;
	while (*it)
	{
		while (*it == '\\')
			if (!*(++it) || !*(++it))
				return (-1);
		ret = checkext(&it, (char *)ext, &pi, r);
		if (ret == -1)
			++it;
		else if (ret == 1 && (--r) == 0)
			return ((int)(it - *s));
		else if (ret == 2 && (r++) == 0)
			*s = it - pi.la;
	}
	return (-1);
}
