/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/06 15:20:50 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>

t_shell	*g_shell;

char	**ft_getpaths(char **envp)
{
	char	*paths;

	if ((paths = ft_getenv("PATH", envp)))
		return (ft_strsplit(paths, ':'));
	return (NULL);
}

void	resetpath(void)
{
	char	**ptr;

	if ((ptr = g_shell->paths))
		while (*ptr)
			free(*ptr++);
	free(g_shell->paths);
	g_shell->paths = ft_getpaths(g_shell->envp);
}

int		ft_getfullpath(char *fname, char **paths, char *fullpath, size_t size)
{
	int		shret;
	char	**it;

	if (fname[0] == '.' || fname[0] == '/')
		return (ft_access(ft_strcat(ft_bzero(fullpath, size), fname), X_OK));
	shret = SH_NFOUND;
	if (!(it = paths))
		return (shret);
	while (*it)
	{
		ft_bzero(fullpath, size);
		ft_strcat(ft_strcatc(ft_strcat(fullpath, *it), '/'), fname);
		if (!access(fullpath, F_OK))
		{
			if (!access(fullpath, X_OK))
				return (SH_OK);
			shret = SH_ADENIED;
		}
		++it;
	}
	*fullpath = '\0';
	return (shret);
}

char	*ft_strshret(t_shret shret)
{
	if (shret == SH_OK)
		return ("success");
	else if (shret == SH_ADENIED)
		return ("permission denied");
	else if (shret == SH_NFOUND)
		return ("command not found");
	else if (shret == SH_NEXIST)
		return ("no such file or directory");
	else if (shret == SH_NDIR)
		return ("not a directory");
	else if (shret == SH_EFAIL)
		return ("operation failed");
	return ("none");
}
