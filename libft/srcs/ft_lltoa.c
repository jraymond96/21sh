/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 14:02:16 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/20 20:42:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"
#include "ft_str.h"
#include "ft_math.h"

int		ft_llonglen(long long n)
{
	int	len;

	len = (n < 0) ? 2 : 1;
	while (n /= 10)
		++len;
	return (len);
}

char	*ft_lltoa(long long n)
{
	char	*str;
	int		i;
	int		isneg;

	isneg = (n < 0) ? 1 : 0;
	i = ft_llonglen(n);
	if ((str = ft_strnew(i)) == NULL)
		return (NULL);
	while (i > 0)
	{
		str[--i] = ft_abs((int)(n % 10)) + 48;
		n /= 10;
	}
	str[0] = (isneg ? '-' : str[0]);
	return (str);
}

char	*ft_lltoa_cbase(long long n, const char *base)
{
	char		*str;
	int			baselen;
	int			i;
	long long	nc;
	int			isneg;

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
