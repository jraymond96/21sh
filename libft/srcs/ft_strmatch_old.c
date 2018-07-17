/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:02:15 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/18 14:27:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_printf.h"

static int	check_chari(char c, const char *match)
{
	char	*til;
	int		pos;
	int		pos1;

	pos = ft_strpbrkl_pos(match, "]");
	if ((pos1 = ft_strnchrl_pos(match, '-', (size_t)pos)) == -1)
	{
		til = ft_strndupl(match, pos);
		pos = ft_strchr_pos(til, c);
		free(til);
		return (pos == -1 ? 0 : 1);
	}
	else if ((til = (char *)&match[pos1 + 1]))
	{
		while (++pos1 < pos)
		{
			match += (*match == '\\' && ++pos1 ? 1 : 0);
			til += (*til == '\\' ? 1 : 0);
			if (c >= *match && c <= *til)
				return (1);
			++match;
			++til;
		}
	}
	return (0);
}

static int	check_char(const char **str, const char **match, int mode)
{
	int	pos;

	if (mode)
	{
		pos = ft_strpbrkl_pos(*match, "]");
		if (!check_chari(**str, *match))
		{
			*match += pos + 1;
			return (0);
		}
		while (check_chari(**str, *match) && **str != *(*match + pos + 1))
			++(*str);
		*match += pos + 1;
	}
	else
	{
		if (((**match == '\\' && ++(*match)) || **match) && **str != **match)
			return (0);
		++(*str);
		++(*match);
	}
	return (1);
}

static int	check_ext(const char **str, const char **match, int *lookup)
{
	if (*(*match + 1) == '[')
	{
		*match += 2;
		if (!check_char(str, match, 1))
			return (0);
		return (2);
	}
	else if (*(*match + 1) == '*' && *(*match + 2) == '[')
		*lookup = 1;
	else if (*(*match + 1) == '\\')
		++(*match);
	if (!*++(*match))
		return (1);
	return (3);
}

static int	fakefunc(const char **str, const char *match, int lookup)
{
	while (**str && **str != *match)
	{
		if (lookup && check_chari(**str, match + 2))
			return (0);
		++(*str);
	}
	return (1);
}

int			ft_strmatch_old(const char *str, const char *match)
{
	int	lookup;
	int	c;

	while (*match)
	{
		lookup = 0;
		if (*match == '\\' && !check_char(&str, &match, 0))
			return (0);
		else if (*match == '*')
		{
			if ((c = check_ext(&str, &match, &lookup)) < 2)
				return (c);
			else if (c == 2)
				continue ;
			if (!fakefunc(&str, match, lookup))
				break ;
			if (!*str)
				return (0);
		}
		else if (*match != '\\' && !check_char(&str, &match, 0))
			return (0);
	}
	return (*str ? 0 : 1);
}
