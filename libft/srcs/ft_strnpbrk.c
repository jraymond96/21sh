/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrpbrk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:02:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/02 21:45:12 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int		ft_strnrpbrk_pos(const char *s, const char *charset, size_t n)
{
	int		i;
	size_t	len;

	len = ft_strlen(s);
	if (n >= len)
		n = len - 1;
	i = n;
	while (i >= 0 && !ft_strchr(charset, s[i]))
		--i;
	return (i);
}

int		ft_strnpbrk_pos(const char *s, const char *charset, size_t n)
{
	size_t	i;

	if (!s || !charset)
		return (-1);
	i = 0;
	while (s[i] && i < n)
	{
		if (ft_strchr(charset, s[i]))
			return ((int)i);
		++i;
	}
	return (-1);
}

int		ft_strnpbrkl_pos(const char *s, const char *charset, size_t n)
{
	size_t	i;
	int		u;

	if (!s || !charset)
		return (-1);
	i = 0;
	u = 1;
	while (s[i] && i < n)
	{
		if (s[i] == '\\' && u)
		{
			++i;
			u = 0;
		}
		else
		{
			if (u && ft_strchr(charset, s[i]))
				return ((int)i);
			u = 1;
			++i;
		}
	}
	return (-1);
}

char	*ft_strnpbrkl(const char *s, const char *charset, size_t n)
{
	int	pos;

	if ((pos = ft_strnpbrkl_pos(s, charset, n)) == -1)
		return (NULL);
	return ((char *)(s + pos));
}
