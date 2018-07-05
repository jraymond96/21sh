/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:38:37 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/18 14:45:50 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"
#include "ft_printf.h"

int		ft_intlen(int n)
{
	int	len;

	len = (n < 0) ? 2 : 1;
	while (n /= 10)
		++len;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		isneg;

	isneg = (n < 0) ? 1 : 0;
	i = ft_intlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[--i] = ft_abs(n % 10) + 48;
		n /= 10;
	}
	str[0] = (isneg ? '-' : str[0]);
	return (str);
}

char	*ft_itoa_cbase(int n, const char *base)
{
	char	*str;
	int		baselen;
	int		i;
	int		nc;
	int		isneg;

	if (!base)
		return (NULL);
	isneg = (n < 0 ? 1 : 0);
	baselen = ft_strlen(base);
	i = (isneg ? 2 : 1);
	nc = n;
	while (nc /= baselen)
		++i;
	if ((str = (char *)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	str[i] = '\0';
	while (i >= 0)
	{
		str[--i] = base[ft_abs(n % baselen)];
		n /= baselen;
	}
	str[0] = (isneg ? '-' : str[0]);
	return (str);
}
