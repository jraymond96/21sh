/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:52:02 by mmerabet          #+#    #+#             */
/*   Updated: 2018/01/16 20:28:56 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_mem.h"

void	ft_lstswap(t_list *a, t_list *b)
{
	size_t	tmp;

	ft_swapptr(&a->content, &b->content);
	tmp = a->content_size;
	a->content_size = b->content_size;
	b->content_size = tmp;
}
