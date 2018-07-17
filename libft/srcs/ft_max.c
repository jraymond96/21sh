/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:06:52 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/02 16:13:56 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int				ft_max(int a, int b)
{
	return (a > b ? a : b);
}

int				ft_min(int a, int b)
{
	return (a < b ? a : b);
}

unsigned int	ft_umax(unsigned int a, unsigned int b)
{
	return (a > b ? a : b);
}

unsigned int	ft_umin(unsigned int a, unsigned int b)
{
	return (a < b ? a : b);
}
