/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:27:32 by mmerabet          #+#    #+#             */
/*   Updated: 2018/04/25 20:07:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"
#include <stdlib.h>

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf(format, args);
	va_end(args);
	return (ret);
}

int		ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf_fd(fd, format, args);
	va_end(args);
	return (ret);
}

int		ft_printf_s(char **buffer, const char *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vprintf_s(buffer, format, args);
	va_end(args);
	return (ret);
}

int		ft_exit(int code, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	exit(code);
	return (ft_strlen(msg));
}

int		ft_exitf(int code, const char *msgf, ...)
{
	va_list	vp;
	int		ret;

	if (msgf)
	{
		va_start(vp, msgf);
		ret = ft_vprintf(msgf, vp);
		va_end(vp);
	}
	exit(code);
	return (ret);
}
