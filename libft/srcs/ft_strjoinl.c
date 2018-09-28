/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 20:08:58 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/23 20:09:44 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoinl(const char *a, const char *b)
{
	char	*s;
	size_t	al;
	size_t	bl;

	al = (a ? ft_strlen(a) : 0);
	bl = (b ? ft_strlenl(b) : 0);
	if (!(s = ft_strnew(al + bl)))
		return ((char *)a);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strcatl(s, b);
	return (s);
}

char	*ft_strnjoinl(const char *a, const char *b, size_t n)
{
	char	*s;
	size_t	al;
	size_t	bl;

	al = (a ? ft_strlen(a) : 0);
	if (n > (bl = (b ? ft_strlenl(b) : 0)))
		n = bl;
	if (!(s = ft_strnew(al + n)))
		return ((char *)a);
	if (a)
		ft_strcat(s, a);
	if (b)
		ft_strncatl(s, b, n);
	return (s);
}

char	*ft_strjoinl_clr(char *a, char *b, int d)
{
	char	*s;

	if (!(s = ft_strjoinl(a, b)))
		return (s);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}

char	*ft_strnjoinl_clr(char *a, char *b, size_t n, int d)
{
	char	*s;

	if (!(s = ft_strnjoinl(a, b, n)))
		return (s);
	if (d == 2 || d == 0)
		free(a);
	if (d == 2 || d == 1)
		free(b);
	return (s);
}
