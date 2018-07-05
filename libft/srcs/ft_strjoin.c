/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:45:25 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/15 17:23:16 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoin(const char *a, const char *b)
{
	char	*s;
	size_t	al;
	size_t	bl;

	al = (a ? ft_strlen(a) : 0);
	bl = (b ? ft_strlen(b) : 0);
	if (!(s = ft_strnew(al + bl)))
		return ((char *)a);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strcat(s, b);
	return (s);
}

char	*ft_strjoin_clr(char *a, char *b, int d)
{
	char	*s;

	if (!(s = ft_strjoin(a, b)))
		return (s);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}
