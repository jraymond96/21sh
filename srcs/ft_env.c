/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:59:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/17 18:20:24 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

int			g_dontfree;

static char	*ft_envitize(char *name, char *value)
{
	char	*res;

	if (!(res = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1)))
		return (NULL);
	return (ft_strcat(ft_strcatc(ft_strcat(res, name), '='), value));
}

int			ft_putenv(char *name, char *value, char ***envp)
{
	size_t	len;

	if (!envp || !name || !value || ft_getenv(name, *envp))
		return (0);
	if (!*envp && !(*envp = (char **)ft_memalloc(sizeof(char **))))
		return (0);
	len = ft_tabsize(*envp);
	if (!((*envp)[len] = ft_envitize(name, value)))
		return (0);
	name = NULL;
	if (!(*envp = (char **)ft_memjoin_clr(*envp,
					sizeof(char *) * (len + 1), &name, sizeof(char *))))
		return (0);
	return (1);
}

char		*ft_getenv(char *name, char **envp)
{
	char	*ename;
	char	**it;

	if (!envp || !name || !(ename = ft_strnew(ft_strlen(name) + 2)))
		return (NULL);
	ft_strcat(ft_strcat(ename, name), "=*");
	it = envp;
	while (*it)
	{
		if (ft_strmatch(*it, ename))
		{
			free(ename);
			return (ft_strchr(*it, '=') + 1);
		}
		++it;
	}
	free(ename);
	return (NULL);
}

int			ft_setenv(char *name, char *value, char ***envp)
{
	char	*ename;
	char	**it;
	size_t	len;

	if (!envp || !name || !value)
		return (0);
	else if (!(ename = ft_getenv(name, *envp)))
		return (ft_putenv(name, value, envp));
	len = ft_strlen(name);
	ename -= len + 1;
	it = *envp;
	while (*it)
	{
		if (ename == *it)
		{
			if (!g_dontfree)
				free(*it);
			*it = ft_envitize(name, value);
			return (1);
		}
		++it;
	}
	return (0);
}

int			ft_unsetenv(char *name, char ***envp)
{
	char	*ename;
	char	**envpl;
	int		i;

	if (!envp || !*envp || !name || !(ename = ft_getenv(name, *envp)))
		return (0);
	else if (!(envpl = (char **)malloc(sizeof(char *) * (ft_tabsize(*envp)))))
		return (0);
	ename -= ft_strlen(name) + 1;
	i = 0;
	while ((*envp)[i])
	{
		if (ename == (*envp)[i] && !(ename = NULL) && !g_dontfree)
			free((*envp)[i]);
		else if (ename != (*envp)[i])
			envpl[(ename ? i : i - 1)] = (*envp)[i];
		++i;
	}
	envpl[i - 1] = NULL;
	free((*envp));
	*envp = envpl;
	return (1);
}
