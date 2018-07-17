/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tobase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:20:40 by mmerabet          #+#    #+#             */
/*   Updated: 2017/12/19 22:26:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_types.h"

char	*ft_tobase(const char *s, char *fbase, char *tbase)
{
	return (ft_lltoa_cbase(ft_atoll_base(s, fbase), tbase));
}
