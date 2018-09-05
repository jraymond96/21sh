/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:49:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/04 15:05:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoinc(const char *a, char b)
{
	char	*s;
	int		len;

	len = (a ? ft_strlen(a) : 0);
	if (!(s = ft_strnew(len + 1)))
		return (NULL);
	if (a)
		ft_strcat(s, a);
	s[len] = b;
	return (s);
}

char	*ft_strjoinc_clr(char *a, char b)
{
	char	*s;

	if ((s = ft_strjoinc(a, b)) == NULL)
		return (NULL);
	free(a);
	return (s);
}
