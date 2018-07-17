/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:27:54 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:44:48 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strmap(char *s, char (*f)(char))
{
	char	*snew;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	if ((snew = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	while (*s)
		snew[i++] = f(*s++);
	snew[i] = '\0';
	return (snew);
}

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	char	*snew;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	if ((snew = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	while (*s)
	{
		snew[i] = f(i, *s++);
		++i;
	}
	snew[i] = '\0';
	return (snew);
}
