/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:22:00 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/02 20:48:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

char	*ft_strclr(char *s)
{
	if (s)
		ft_bzero((void *)s, ft_strlen(s));
	return (s);
}

char	*ft_strnclr(char *s, size_t n)
{
	size_t	l;

	l = ft_strlen(s);
	if (n > l)
		n = l;
	if (s)
		ft_bzero((void *)s, n);
	return (s);
}
