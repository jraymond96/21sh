/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swapptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:47:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/10 22:58:14 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	ft_swapptr(void **a, void **b)
{
	void	*tmp;

	if (!a || !b)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_pair	ft_make_pair(void *a, void *b)
{
	t_pair	pr;

	pr.a = a;
	pr.b = b;
	return (pr);
}
