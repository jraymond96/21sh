/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:45:25 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/02 10:50:15 by mmerabet         ###   ########.fr       */
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

char	*ft_strnjoin(const char *a, const char *b, size_t n)
{
	char	*s;
	size_t	al;
	size_t	bl;

	al = (a ? ft_strlen(a) : 0);
	if (n > (bl = (b ? ft_strlen(b) : 0)))
		n = bl;
	if (!(s = ft_strnew(al + n)))
		return ((char *)a);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strncat(s, b, n);
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

char	*ft_strnjoin_clr(char *a, char *b, size_t n, int d)
{
	char	*s;

	if (!(s = ft_strnjoin(a, b, n)))
		return (s);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}
