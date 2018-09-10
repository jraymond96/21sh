/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsepath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 02:04:13 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/05 22:39:59 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <unistd.h>
#include <sys/stat.h>

static void	performclr(char *pwd, char **nms)
{
	int	pos;
	int	n;

	n = 0;
	if (ft_strequ(*nms, ".."))
	{
		if (pwd[(pos = ft_strlen(pwd) - 1)] == '/')
		{
			pwd[pos] = '\0';
			pos = ft_strrchr_pos(pwd, '/');
			ft_strclr(pos == -1 ? pwd : pwd + pos);
		}
	}
	else if (ft_strcat(pwd, *nms))
		n = 1;
	if (*(nms + 1) || (!n && !*pwd))
		ft_strcatc(pwd, '/');
}

char		*ft_parsepath(char *target, char *origin, size_t size)
{
	char	**nms;
	char	**ptr;
	char	*end;

	if (!(nms = ft_strsplit(target, '/')))
		return (origin);
	if ((ptr = nms) && *target == '/')
		ft_bzero(origin, size);
	if (*target == '/' || (*origin && origin[ft_strlen(origin) - 1] != '/'))
		ft_strcatc(origin, '/');
	while (*nms)
	{
		if (!ft_strequ(*nms, "."))
			performclr(origin, nms);
		free(*nms++);
	}
	if (*(end = ft_strend(origin)) == '/' && end != origin)
		*end = '\0';
	free(ptr);
	return (origin);
}

int			ft_chdir(char *target, char *pwd, size_t size, int slink)
{
	t_shret		acc;
	struct stat	st;
	char		tmp[2048];

	acc = SH_NFOUND;
	ft_strcpy(ft_bzero(tmp, 2048), pwd);
	if ((acc = ft_access(ft_parsepath(target, pwd, size), R_OK)) != SH_OK)
		return (ft_strcpy(ft_bzero(pwd, size), tmp) ? acc : acc);
	if (stat(pwd, &st) == -1 || !S_ISDIR(st.st_mode))
		return (ft_strcpy(ft_bzero(pwd, size), tmp) ? SH_NDIR : SH_NDIR);
	if (chdir(slink ? pwd : target) == -1)
		return (ft_strcpy(ft_bzero(pwd, size), tmp) ? SH_EFAIL : SH_EFAIL);
	if (!slink)
		ft_getcwd(pwd, size);
	return (SH_OK);
}

int			ft_chdirl(char *target, char *pwd, size_t size)
{
	return (ft_chdir(target, pwd, size, 0));
}
