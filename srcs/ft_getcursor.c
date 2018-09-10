/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:36:17 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/12 12:18:01 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_str.h"
#include <termios.h>
#include <sys/ioctl.h>

void	ft_getcursor(int *x, int *y)
{
	int	c;
	int	nx;
	int	ny;

	if (!x && !y)
		return ;
	nx = 0;
	ny = 0;
	ft_makeraw(1);
	ft_putstr("\033[6n");
	if (ft_getch() && ft_getch())
	{
		while ((c = ft_getch()) != ';')
			ny = ny * 10 + (c - 48);
		while ((c = ft_getch()) != 'R')
			nx = nx * 10 + (c - 48);
	}
	ft_makeraw(0);
	if (x)
		*x = nx;
	if (y)
		*y = ny;
}

void	ft_getsize(int *row, int *col)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (col)
		*col = w.ws_col;
	if (row)
		*row = w.ws_row;
}

void	ft_makeraw(int setb)
{
	static int				isset;
	static struct termios	origt;
	struct termios			newt;

	if (setb && !isset)
	{
		isset = 1;
		tcgetattr(0, &origt);
		ft_memcpy(&newt, &origt, sizeof(struct termios));
		newt.c_lflag &= ~(ICANON | ECHO | ISIG);
		newt.c_iflag &= ~ICRNL;
		newt.c_cflag &= ~CREAD;
		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &newt);
	}
	else if (isset)
		tcsetattr((isset = 0), TCSANOW, &origt);
}

char	**ft_getoptl(char **argv, char option, const char *loption,
		int lfirst)
{
	t_opt	opt;
	int		ret;
	char	*options;
	char	**ptr;

	if (!(options = ft_strnew((loption ? ft_strlen(loption) : 0) + 6)))
		return (NULL);
	ft_strcat(ft_strcatc(options, option), ".1");
	if (loption && ft_strcatc(options, ';'))
		ft_strcat(ft_strcat(options, loption), ".1");
	ptr = NULL;
	while ((ret = ft_getopt(&argv, options, &opt)) != OPT_END)
	{
		if (ret != OPT_UNKNOWN && (opt.c == option
					|| (opt.c == '-' && ft_strequ(opt.clong, loption))))
		{
			ptr = opt.ptr;
			if (!lfirst)
				break ;
		}
	}
	free(options);
	return (ptr);
}

int		ft_access(char *filename, int tests)
{
	if (!access(filename, F_OK))
	{
		if (!access(filename, tests))
			return (SH_OK);
		return (SH_ADENIED);
	}
	return (SH_NEXIST);
}
