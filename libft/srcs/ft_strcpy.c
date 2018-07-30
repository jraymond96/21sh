/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:42:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/17 14:46:19 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (*src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src)
		while (i < n && *src)
			dst[i++] = *src++;
	while (i < n)
		dst[i++] = '\0';
	return (dst);
}
