/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepeat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 20:38:08 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:41:29 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

char	*ft_strrepeat(const char *s, int n)
{
	char	*result;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	len *= n;
	if (!(result = ft_strnew(len)))
		return (NULL);
	while (n--)
		ft_strcat(result, s);
	return (result);
}

char	*ft_strrepeat_clr(char *s, int n)
{
	char	*result;

	result = ft_strrepeat(s, n);
	free(s);
	return (result);
}
