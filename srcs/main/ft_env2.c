/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:29:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/09 23:52:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

void		ft_delenv(char ***envp)
{
	char	**it;

	if (!(it = *envp))
		return ;
	while (*it)
		ft_memdel((void **)it++);
	free(*envp);
	*envp = NULL;
}

char		**ft_copyenv(char **envp)
{
	char	**newenv;
	size_t	i;

	if (!envp || !(newenv =
				(char **)ft_memalloc(sizeof(char *) * (ft_tabsize(envp) + 1))))
		return (NULL);
	i = 0;
	while (*envp)
	{
		if (!(newenv[i++] = ft_strdup(*envp)))
		{
			ft_delenv(&newenv);
			return (NULL);
		}
		++envp;
	}
	return (newenv);
}

int			ft_modenv(char *str, char ***envp)
{
	char	*name;
	char	*value;
	int		ret;

	if (!str || !envp || !(value = ft_strchr(str, '=')))
		return (0);
	name = str;
	*value++ = '\0';
	ret = ft_setenv(name, value, envp);
	*(value - 1) = '=';
	return (ret);
}

char		**ft_mergeenv(char ***a, char **b)
{
	if (!a)
		return (b);
	if (!*a || !b)
		return (*a);
	while (*b)
		ft_modenv(*b++, a);
	return (*a);
}
