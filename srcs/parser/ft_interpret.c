/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:35:11 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/20 21:52:08 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_printf.h"

int			ft_interpret(const char *command, void *ptr, t_lexerf *lexf,
					t_iterf *itf)
{
	t_ast	*head;
	int		ret;

	ret = -1;
	if (!(head = ft_lexer(command, lexf)))
		return (ret);
	ret = ft_astiter(head, ptr, itf);
	ft_astdel(&head);
	return (ret);
}
