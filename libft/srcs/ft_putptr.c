/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:44:23 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 20:32:42 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_types.h"

void	ft_putptr(void *ptr)
{
	ft_putptr_fd(ptr, 1);
}

void	ft_putptr_fd(void *ptr, int fd)
{
	ft_putstr_fd("0x", fd);
	ft_putullong_base_fd((unsigned long long)ptr, FT_HEX, fd);
}
