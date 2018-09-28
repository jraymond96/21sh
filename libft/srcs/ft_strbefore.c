/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbefore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:10:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/01 20:39:23 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strbefore(const char *s, char a)
{
	int	pos;

	if (!s)
		return (NULL);
	pos = ft_strchr_pos(s, a);
	return (pos == -1 ? NULL : ft_strndup(s, pos));
}

char	*ft_strbeforestr(const char *s, const char *a)
{
	int	pos;

	if (!s || !a)
		return (NULL);
	pos = ft_strstr_pos(s, a);
	return (pos == -1 ? NULL : ft_strndup(s, pos));
}
