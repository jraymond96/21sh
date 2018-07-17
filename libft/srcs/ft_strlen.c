/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:42:54 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/10 23:00:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_types.h"
#include "ft_mem.h"

static t_pair	g_escseq[] = {
	{"n", "\n"}, {"t", "\t"}, {"b", "\b"}, {"a", "\a"}, {"f", "\f"},
	{"r", "\r"}, {"v", "\v"}, {"e", "\e"}
};
static int		g_escseq_n = sizeof(g_escseq) / sizeof(t_pair);

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			++i;
	return (i);
}

size_t		ft_strlenl(const char *s)
{
	size_t	i;
	int		n;

	i = 0;
	n = 1;
	if (!s)
		return (0);
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
			++i;
			++s;
		}
	}
	return (i);
}

size_t		ft_strlenli(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\\')
		{
			if (*++s)
				++s;
		}
		else
		{
			++i;
			++s;
		}
	}
	return (i);
}

static int	checkescseq(const char **s)
{
	int	j;

	j = -1;
	while (++j < g_escseq_n)
		if (**s == *(char *)g_escseq[j].a && (*s)++)
			break ;
	if (j == g_escseq_n)
	{
		j = 0;
		if (**s == 'x')
			while (*++(*s) && ft_strchr(FT_HEX, ft_tolower(**s)) && j < 2)
				++j;
		else if (ft_strchr(FT_OCT, **s))
			while (*++(*s) && ft_strchr(FT_OCT, **s) && j < 2)
				++j;
		else
			++(*s);
		if (!**s)
			return (1);
	}
	return (0);
}

size_t		ft_strlenk(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		if (*s == '\\')
		{
			if (!*++s)
				return (i);
			++i;
			if (checkescseq(&s))
				return (i);
			continue;
		}
		else
			++i;
		++s;
	}
	return (i);
}
