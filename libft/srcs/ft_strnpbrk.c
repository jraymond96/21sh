/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrpbrk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:02:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/28 16:10:51 by mmerabet         ###   ########.fr       */
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

int		ft_strnpbrkl_pos(const char *s, const char *charset, size_t n)
{
	char	*sc;
	char	tmp;
	int		len;

	sc = (char *)s;
	if (n > (size_t)(len = ft_strlen(s)))
		n = (size_t)len;
	tmp = sc[n];
	sc[n] = '\0';
	len = ft_strpbrkl_pos(sc, charset);
	sc[n] = tmp;
	return (len);
}

char	*ft_strnpbrkl(const char *s, const char *charset, size_t n)
{
	char	*sc;
	char	tmp;
	size_t	len;
	char	*ptr;

	sc = (char *)s;
	if (n > (len = ft_strlen(s)))
		n = len;
	tmp = sc[n];
	sc[n] = '\0';
	ptr = ft_strpbrkl(sc, charset);
	sc[n] = tmp;
	return (ptr);
}
