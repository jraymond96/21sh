/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 22:05:26 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:40:41 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_revstr(char *a)
{
	size_t	i;
	size_t	len;

	if (!a)
		return (NULL);
	i = 0;
	len = ft_strlen(a) - 1;
	while (i < len)
		ft_swap(a + i++, a + len--);
	return (a);
}

char	*ft_revnstr(char *a, size_t n)
{
	size_t	i;

	if (!a)
		return (NULL);
	i = ft_strlen(a) - 1;
	n = (n > i ? i : n);
	i = 0;
	while (i < n)
		ft_swap(a + i++, a + n--);
	return (a);
}
