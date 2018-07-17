/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:03:46 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 19:25:23 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"

long	ft_atol(const char *s)
{
	long				nb;
	int					sign;

	if (!s)
		return (0);
	nb = 0;
	sign = 1;
	while (ft_isspace(*s))
		++s;
	if ((*s == '+' || *s == '-') && *s++ == '-')
		sign = -1;
	while (ft_isdigit(*s))
		nb = nb * 10 + (*s++ - 48);
	return (nb * sign);
}
