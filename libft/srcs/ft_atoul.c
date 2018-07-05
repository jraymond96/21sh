/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 14:01:04 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 19:27:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"

unsigned long	ft_atoul(const char *s)
{
	unsigned long	nb;

	if (!s)
		return (0);
	nb = 0;
	while (ft_isspace(*s))
		++s;
	while (ft_isdigit(*s))
		nb = nb * 10 + (*s++ - 48);
	return (nb);
}
