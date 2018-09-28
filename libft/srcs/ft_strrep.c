/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:44:59 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 21:50:19 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strrep(const char *s, char a, char b)
{
	char	*snew;
	char	*pos;

	if (!s || (snew = ft_strdup(s)) == NULL)
		return (NULL);
	pos = snew;
	while ((pos = ft_strchr(pos, a)))
		*pos++ = b;
	return (snew);
}

char	*ft_strrep_clr(char *s, char a, char b)
{
	char	*snew;
	char	*pos;

	if ((snew = ft_strdup(s)) == NULL)
		return (NULL);
	pos = snew;
	while ((pos = ft_strchr(pos, a)))
		*pos++ = b;
	free(s);
	return (snew);
}

char	*ft_strrepc(char *s, char a, char b)
{
	char	*it;

	if (!(it = s))
		return (NULL);
	while (*it)
	{
		if (*it == a)
			*it = b;
		++it;
	}
	return (s);
}

char	*ft_strrepc_str(char *s, const char *a, const char *b)
{
	char	*it;
	int		pos;
	int		len;

	if (!(it = s))
		return (NULL);
	len = ft_strlen(b);
	while (*it)
	{
		if ((pos = ft_strchr_pos(a, *it)) != -1 && pos < len)
			*it = b[pos];
		++it;
	}
	return (s);
}
