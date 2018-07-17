/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:09:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/10 20:12:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

static int	ft_count_words(const char *s, char sep)
{
	int	count;
	int	pos;

	count = 0;
	while (s)
	{
		pos = ft_strchr_pos(s, sep);
		if (pos != 0 && s[0])
			++count;
		s = (pos != -1 ? s + (pos + 1) : NULL);
	}
	return (count);
}

char		**ft_strsplit(const char *s, char sep)
{
	char	**t;
	int		sz;
	int		pos;

	if (!s)
		return (NULL);
	t = NULL;
	sz = 0;
	t = (char **)ft_memalloc(sizeof(char *) * (ft_count_words(s, sep) + 1));
	if (t == NULL)
		return (NULL);
	while (s)
	{
		pos = ft_strchr_pos(s, sep);
		if (pos != 0 && s[0])
			t[sz++] = (pos != -1 ? ft_strndup(s, pos) : ft_strdup(s));
		s = (pos != -1 ? s + (pos + 1) : NULL);
	}
	return (t);
}

static int	ft_count_words_str(const char *s, const char *sep)
{
	int	count;
	int	pos;
	int	seplen;

	seplen = ft_strlen(sep);
	count = 0;
	while (s)
	{
		pos = ft_strstr_pos(s, sep);
		if (pos != 0 && s[0])
			++count;
		s = (pos != -1 ? s + (pos + seplen) : NULL);
	}
	return (count);
}

char		**ft_strsplitstr(const char *s, const char *sep)
{
	char	**t;
	int		sz;
	int		pos;
	size_t	seplen;

	if (!s || !sep)
		return (NULL);
	seplen = ft_strlen(sep);
	t = (char **)ft_memalloc(sizeof(char *) * (ft_count_words_str(s, sep) + 1));
	if (t == NULL)
		return (NULL);
	sz = 0;
	while (s)
	{
		pos = ft_strstr_pos(s, sep);
		if (pos != 0 && s[0])
			t[sz++] = (pos != -1 ? ft_strndup(s, pos) : ft_strdup(s));
		s = (pos != -1 ? s + (pos + seplen) : NULL);
	}
	return (t);
}

size_t		ft_tabsize(char **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
	while (*tab++)
		++i;
	return (i);
}
