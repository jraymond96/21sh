/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 23:02:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/04 22:04:59 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "ft_list.h"
#include "ft_mem.h"
#include "ft_str.h"

static t_fd	*get_fd(t_list **lst, int fd)
{
	t_list	*lst_fd;
	t_fd	tmp_fd;

	tmp_fd.fd = fd;
	if (!(lst_fd = ft_lstfindm(*lst, &tmp_fd, 0, sizeof(int))))
	{
		ft_bzero(tmp_fd.buffer, BUFF_SIZE + 1);
		tmp_fd.len = 0;
		lst_fd = ft_lstpush(*lst, ft_lstnew(&tmp_fd, sizeof(t_fd)));
		if (*lst == NULL)
			*lst = lst_fd;
	}
	return (lst_fd ? (t_fd *)lst_fd->content : NULL);
}

static int	inner_get_next_delim(t_fd *fd, char **l, const char *delim, int n)
{
	int	bread;
	int	len;

	len = 0;
	if (fd->len <= 0)
		fd->len = read(fd->fd, fd->buffer, BUFF_SIZE);
	while (fd->len > 0)
	{
		if ((bread = ft_memstr_pos(fd->buffer, fd->len, delim, n)) == -1)
			bread = fd->len;
		fd->buffer[bread] = '\0';
		*l = ft_memjoin_clr(*l, len, fd->buffer, bread + 1);
		if (bread < fd->len)
		{
			fd->len -= bread + 1;
			ft_memcpy(fd->buffer, fd->buffer + (bread + 1), fd->len);
			return (len + bread);
		}
		len += fd->len;
		fd->len = read(fd->fd, fd->buffer, BUFF_SIZE);
	}
	if (!*l && fd->len == 0)
		return (-2);
	return (*l ? len : fd->len);
}

int			get_next_delim(const int fd, char delim, char **line)
{
	static t_list	*fds;
	t_fd			*curr_fd;

	if (fd < 0 || !line || !(curr_fd = get_fd(&fds, fd)))
		return (-1);
	*line = NULL;
	return (inner_get_next_delim(curr_fd, line, &delim, 1));
}

int			get_next_delimstr(const int fd, const char *delim, char **line)
{
	static t_list	*fds;
	t_fd			*curr_fd;

	if (fd < 0 || !line || !delim || !(curr_fd = get_fd(&fds, fd)))
		return (-1);
	*line = NULL;
	return (inner_get_next_delim(curr_fd, line, delim, ft_strlen(delim)));
}

int			get_next_line(const int fd, char **line)
{
	return (get_next_delim(fd, '\n', line));
}
