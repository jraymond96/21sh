/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 20:48:31 by mmerabet          #+#    #+#             */
/*   Updated: 2018/02/15 21:47:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_str.h"

void	ft_hextorgba(int color, unsigned char rgba[4])
{
	rgba[0] = (color & 0xff000000) >> (8 * 3);
	rgba[1] = (color & 0xff0000) >> (8 * 2);
	rgba[2] = (color & 0xff00) >> 8;
	rgba[3] = color & 0xff;
}

void	ft_hextorgb(int color, unsigned char rgba[3])
{
	rgba[0] = (color & 0xff0000) >> (8 * 2);
	rgba[1] = (color & 0xff00) >> 8;
	rgba[2] = color & 0xff;
}
