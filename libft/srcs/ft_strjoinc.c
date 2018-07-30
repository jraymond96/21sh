/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:49:58 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:44:01 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoinc(const char *a, char b)
{
	char	*s;

	if ((s = ft_strmdup(a, 1)) == NULL)
		return (NULL);
	s[ft_strlen(a)] = b;
	return (s);
}

char	*ft_strjoinc_clr(char *a, char b)
{
	char	*s;

	if ((s = ft_strmdup(a, 1)) == NULL)
		return (NULL);
	s[ft_strlen(a)] = b;
	free(a);
	return (s);
}
