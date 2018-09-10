/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:23:36 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:40:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"

int		ft_ullonglen(unsigned long long n)
{
	int	len;

	len = 1;
	while (n /= 10)
		++len;
	return (len);
}

char	*ft_ulltoa(unsigned long long n)
{
	char	*str;
	int		i;

	i = ft_ullonglen(n);
	if ((str = ft_strnew(i)) == NULL)
		return (NULL);
	while (i > 0)
	{
		str[--i] = ft_abs((int)(n % 10)) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_ulltoa_cbase(unsigned long long n, const char *base)
{
	char				*str;
	int					baselen;
	int					i;
	unsigned long long	nc;

	if (!base)
		return (NULL);
	baselen = ft_strlen(base);
	i = 1;
	nc = n;
	while (nc /= baselen)
		++i;
	if ((str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = base[ft_abs(n % baselen)];
		n /= baselen;
	}
	return (str);
}
