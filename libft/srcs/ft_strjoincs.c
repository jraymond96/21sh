/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoincs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:51:22 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 21:44:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strjoincs(char a, const char *b)
{
	char	*s;
	size_t	i;

	i = 0;
	if ((s = ft_strnew(ft_strlen(b) + 1)) == NULL)
		return (NULL);
	s[i++] = a;
	if (b)
		while (*b)
			s[i++] = *b++;
	return (s);
}

char	*ft_strjoincs_clr(char a, char *b)
{
	char	*s;
	char	*sb;
	size_t	i;

	i = 0;
	sb = b;
	if ((s = ft_strnew(ft_strlen(b) + 1)) == NULL)
		return (NULL);
	s[i++] = a;
	if (b)
		while (*b)
			s[i++] = *b++;
	b = NULL;
	free(sb);
	return (s);
}
