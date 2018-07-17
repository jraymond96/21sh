/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:23:41 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/10 23:02:15 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"

static t_pair	g_escseq[] = {
	{"n", "\n"}, {"t", "\t"}, {"b", "\b"}, {"a", "\a"}, {"f", "\f"},
	{"r", "\r"}, {"v", "\v"}, {"e", "\e"}
};
static int		g_escseq_n = sizeof(g_escseq) / sizeof(t_pair);

char		*ft_strdupl(const char *s)
{
	size_t	i;
	int		n;
	char	*str;

	if (!s || !(str = ft_strnew(ft_strlenl(s))))
		return (NULL);
	i = 0;
	n = 1;
	while (*s)
	{
		if (*s == '\\' && n)
		{
			++s;
			n = 0;
		}
		else
		{
			n = 1;
			str[i++] = *s++;
		}
	}
	return (str);
}

char		*ft_strndupl(const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	int		u;
	char	*str;

	if (!s || !(str = ft_strnew(ft_strlenl(s))))
		return (NULL);
	i = 0;
	j = 0;
	u = 1;
	while (s[j] && j < n)
	{
		if (s[j] == '\\' && u)
			u = 0;
		else
		{
			u = 1;
			str[i++] = s[j];
		}
		++j;
	}
	return (str);
}

static char	checkescseq(const char **s)
{
	int		j;
	char	cs[4];

	ft_bzero(cs, 4);
	j = -1;
	while (++j < g_escseq_n)
		if (**s == *(char *)g_escseq[j].a && (*s)++)
			return (*(char *)g_escseq[j].b);
	if (j == g_escseq_n)
	{
		j = 0;
		if (**s == 'x')
		{
			while (*++(*s) && ft_strchr(FT_HEX, ft_tolower(**s)) && j < 2)
				cs[j++] = **s;
			return ((char)ft_atoi_basec(cs, FT_HEX));
		}
		else if (ft_strchr(FT_OCT, **s) && (cs[j++] = **s))
		{
			while (*++(*s) && ft_strchr(FT_OCT, **s) && j < 3)
				cs[j++] = **s;
			return ((char)ft_atoi_basec(cs, FT_OCT));
		}
	}
	return (*(*s)++);
}

char		*ft_strdupk(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || !(str = ft_strnew(ft_strlenk(s))))
		return (NULL);
	while (*s)
	{
		if (*s == '\\')
		{
			if (!*++s)
				return (str);
			str[i++] = checkescseq(&s);
			continue;
		}
		else
			str[i++] = *s;
		++s;
	}
	return (str);
}
