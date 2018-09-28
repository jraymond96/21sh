/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/19 20:01:27 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>

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
		ft_strlcat(ft_strcatc(ft_strcat(fullpath, *it), '/'), fname, size);
		if (!access(fullpath, F_OK))
		{
			if (!access(fullpath, X_OK))
				return (SH_OK);
			shret = SH_ADENIED;
		}
		++it;
	}
	return (shret);
}

static t_op	g_shellerrs[] = {
	{"success", SH_OK},
	{"malloc failed", SH_MALLOC},
	{"permission denied", SH_ADENIED},
	{"command not found", SH_NFOUND},
	{"no such file or directory", SH_NEXIST},
	{"not a directory", SH_NDIR},
	{"not a file", SH_NFILE},
	{"operation failed", SH_EFAIL},
	{"operation success", SH_ESUCCESS},
	{"pipe has failed", SH_PIPFAIL},
	{"dup failed", SH_DUPFAIL},
	{"fork failed", SH_FORKFAIL},
	{"exec format error", SH_EXECERR},
	{"could not open file", SH_OPENFILE},
	{"bad file descriptor", SH_BADFD},
	{"parse error", SH_BADEXPR},
	{"HOME not set", SH_NHOME},
	{"OLDPWD not set", SH_NOLDPWD},
	{"failed to open temporary file for heredoc (writing)", SH_HDOCWFAIL},
	{"failed to open temporary file for heredoc (reading)", SH_HDOCRFAIL},
	{"missing WORD delimiter for heredoc", SH_HDOCWORD},
	{"maximum of background processes reached", SH_MAXBGPROC},
	{"condition statement without then", SH_CONDWTHEN},
	{"then without previous condition statement", SH_THENWCOND},
	{"else without previous condition statement", SH_ELSEWCOND},
	{"none", SH_NONE}, {NULL, SH_EXIT}
};
static size_t	g_shellerrs_len = (sizeof(g_shellerrs) / sizeof(t_op));

char	*ft_strshret(int shret)
{
	size_t	i;

	i = 0;
	if (shret > SH_EXPRERR)
		return (ft_exprerr(shret - SH_EXPRERR));
	while (i < g_shellerrs_len)
	{
		if (shret == g_shellerrs[i].t)
			return (g_shellerrs[i].name);
		++i;
	}
	return (NULL);
}

int		ft_printshret(int shret, char *name)
{
	char	*str;

	if (!(str = ft_strshret(shret)))
		return (1);
	if (name)
		ft_printf_fd(2, "%s: %s: %s\n", g_shell->name, ft_strshret(shret),
				name);
	else
		ft_printf_fd(2, "%s: %s\n", g_shell->name, ft_strshret(shret));
	return (1);
}
