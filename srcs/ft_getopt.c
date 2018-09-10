/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:36:37 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/04 03:19:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

/*
** The working of this getopt version is similar to the real one, but has
** some differencies.
**
** There can be 5 different return values:
** OPT_END, OPT_MISSING, OPT_UNKNOWN, OPT_ALAST and OPT_OK.
** OPT_END: This means that we, either reached the end of the array, or there
** is no options anymore.
** OPT_MISSING: There are arguments missing for the returned character option.
** OPT_UNKNOWN: The character option is unknown and is not present in the string
** containing the character options.
** OPT_ALAST: When a character option is awaiting arguments it should be alone:
** "-l ..." or at the end of a sequence of options "-xxxl ...", This return
** tells that the character option has not been caught at the end of a sequence
** of options "-xlxx ..." so the argument following the 'l' option are not 'l's
** arguments.
** OPT_OK: No problem has been caught.
**
** [char ***argv] ->
** The first parameter is a pointer to an array of strings (the address of
** argv), the function needs it in order to move through the array between The
** calls. The function assume that argv[0] is not a part of the array.
**
** [const char *options] ->
** The second parameter is a string containing each option characters. An
** option character can take a defined number of arguments if it is followed by
** a dot and a number telling how much argument there must be after the
** character: "l.2a.4" <- the 4 arguments that follows 'a' are 'a's arguments,
** and the 2 arguments that follows 'l' are 'l's arguments.
**
** [t_opt *opt]
** The third, and last, parameter is a pointer to a structure where will be
** stored additional, but important, information about the current option.
** -> the 'c' attribute is the character option. If 'l' character option
** is caught, then c is equal to that character.
** -> the 'n' attribute tells how many arguments were successfully caught
** after the character option. It is equal to zero if the option is not waiting
** any arguments.
** -> the 'ptr' attribute points to the first argument after the character
** option. It is equal to NULL if the option is not waiting any arguments.
** -> the 'seq' attribute is a little bit useless here, it just tells if the
** option is in a sequence of option "-abcd" or not, and where.
** There are 4 different values, 1: At the beginning of a sequence "-Axxx",
** 2: In the middle of a sequence "-xAAAx", 3: At the end of a
** sequence "-xxxA", and, finally 0: Has not been caught in a sequence "-A".
** The usefullness of such a variable can be debated.
*/

static int	getnargs(char c, const char *options, char *cs, char *p)
{
	char	cf[3];

	*(ft_strcpy(cf + 1, ";") - 1) = c;
	if (c != '.' && c != ' ' && !ft_isdigit(c)
			&& (cs = ft_strpbrk(options, cf)) && *cs != ';')
	{
		if (*(cs + 1) != '.')
			return (0);
		return (ft_isdigit(*(cs + 2)) ? ft_atoi(cs + 2) : 1);
	}
	else if (ft_isdigit(c) && (cs = (char *)options))
	{
		while (*cs && (cs = ft_strpbrk(cs, cf)) && *cs != ';')
		{
			p = cs++;
			while (p != options && ft_isdigit(*p))
				--p;
			if (*p != '.' && *cs != '.')
				return (0);
			else if (*p != '.')
				return (ft_isdigit(*(cs + 1)) ? ft_atoi(cs + 1) : 1);
		}
	}
	return (-2);
}

static int	getnpargs(char *s, const char *options, t_opt *opt)
{
	size_t	l;

	if (*s == '-')
	{
		l = ft_strlen(++s);
		while ((options = ft_strchr(options, ';')))
		{
			if (ft_strnequ(s, ++options, l))
			{
				if (*(options += l) != '.')
					return (0);
				return (ft_isdigit(*(options + 1)) ? ft_atoi(options + 1) : 1);
			}
		}
		opt->clong = s;
		return (-2);
	}
	return (-1);
}

static int	getcargs(t_opt *opt, char ***argv)
{
	int	i;

	i = 0;
	while (i < opt->n && **argv)
	{
		if (ft_strequ(**argv, "--"))
			break ;
		++(*argv);
		++i;
	}
	if (i < opt->n)
	{
		opt->n = i;
		return (OPT_MISSING);
	}
	return (OPT_OK);
}

static int	checkargs(char ***argv, const char *options, t_opt *opt, int *isopt)
{
	char	*str;

	if ((str = *(*argv - 1)) && !*isopt && *str == '-' && !*++str)
		return (OPT_EMPTY);
	opt->c = *str;
	if ((opt->n = getnpargs(str, options, opt)) != -1 && opt->n != -2)
		opt->clong = str + 1;
	else if (opt->n != -2 && (opt->n = getnargs(*str, options, 0, 0)) == -2)
	{
		*isopt = (!*(str + 1) ? 0 : *isopt);
		if (*(str + 1) && (*isopt = 1))
		{
			opt->seq = (!opt->seq ? 1 : opt->seq);
			*--(*argv) = str + 1;
		}
	}
	else if (opt->n != -2 && *(str + 1) && (*isopt = 1))
	{
		opt->seq = (!opt->seq ? 1 : opt->seq);
		*--(*argv) = str + 1;
		return (opt->n > 0 && !(opt->n = 0) ? OPT_ALAST : OPT_OK);
	}
	if (opt->n == -2)
		return (OPT_UNKNOWN);
	return (!(*isopt = 0) ? getcargs(opt, argv) : OPT_OK);
}

int			ft_getopt(char ***argv, const char *options, t_opt *opt)
{
	static int	isopt;
	static char	**ptr;

	if (!argv || !*argv || !**argv || !options || !opt)
		return (opt ? (opt->ret = OPT_END) : OPT_END);
	if (ptr != *argv)
		isopt = 0;
	ptr = *argv;
	if (!isopt)
		opt->cur = **argv;
	if (***argv == '-' || isopt)
	{
		opt->ptr = ++(*argv);
		ft_bzero(&opt->n, sizeof(int) * 5);
		if (isopt)
			opt->seq = (!*(*ptr + 1) ? 3 : 2);
		if (!isopt && ft_strequ(*(*argv - 1), "--"))
			return ((opt->ret = OPT_END));
		opt->ret = checkargs(argv, options, opt, &isopt);
		if (opt->seq == 3)
			*(*argv - 1) = opt->cur;
		return (opt->ret);
	}
	return ((opt->ret = OPT_END));
}
