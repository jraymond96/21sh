/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strafter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:58:30 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:41:03 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strafter(const char *s, char a)
{
	char	*pos;

	if (!s)
		return (NULL);
	pos = ft_strchr(s, a);
	return (pos == NULL ? NULL : ft_strdup(pos + 1));
}

char	*ft_strafterstr(const char *s, const char *a)
{
	char	*pos;

	if (!s || !a)
		return (NULL);
	pos = ft_strstr(s, a);
	return (pos == NULL ? NULL : ft_strdup(pos + ft_strlen(a)));
}
