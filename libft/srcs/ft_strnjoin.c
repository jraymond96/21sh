/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 10:51:26 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/02 22:10:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strn2join(const char *a, const char *b, size_t n)
{
	char	*s;
	size_t	al;
	size_t	bl;

	if (n > (al = (a ? ft_strlen(a) : 0)))
		n = al;
	bl = (b ? ft_strlen(b) : 0);
	if (!(s = ft_strnew(n + bl)))
		return ((char *)a);
	if (a)
		ft_strncat(s, a, n);
	if (b)
		ft_strcat(s, b);
	return (s);
}

char	*ft_strn2join_clr(char *a, char *b, size_t n, int d)
{
	char	*s;

	if (!(s = ft_strn2join(a, b, n)))
		return (s);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}
