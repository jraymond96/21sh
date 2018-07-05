/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbetweenps.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:08:44 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/28 16:08:57 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int		ft_strbetweenps(char **s, const char *a, const char *b)
{
	int		len[2];
	char	*it;
	int		r;

	if (!s || !*s || !a || !b || (len[0] = ft_strstrl_pos(*s, a)) == -1)
		return (-1);
	*s += len[0];
	len[0] = (int)ft_strlen(a);
	len[1] = (int)ft_strlen(b);
	it = *s + len[0] - 1;
	r = 1;
	while (*++it)
	{
		if (*it == '\\' && !*(++it))
			break ;
		else if (*(it - 1) != '\\' && ft_strnequ(it, b, len[1]))
		{
			if (--r == 0)
				return ((it + len[1]) - *s);
		}
		else if (*(it - 1) != '\\' && ft_strnequ(it, a, len[0]))
			++r;
	}
	return (-1);
}

char	*ft_strbetweenstr(const char *s, const char *a, const char *b)
{
	char	*it;
	int		len;
	int		alen;

	it = (char *)s;
	if ((len = ft_strbetweenps(&it, a, b)) == -1)
		return (NULL);
	alen = (int)ft_strlen(a);
	len -= alen - (int)ft_strlen(b);
	return (ft_strndup(it + alen, len - alen - (int)ft_strlen(b)));
}

int		checkwild3(const char **str, t_mchi *cur, t_mchi *nxt, int n)
{
	char		*ptr;
	int			len;

	(void)nxt;
	ptr = (char *)*str;
	if ((len = ft_strbetweenps_ext(&ptr, cur->str)) == -1 || ptr > *str)
		return (-1);
	g_iread += len;
	if (n)
		*str += len;
	return (1);
}
