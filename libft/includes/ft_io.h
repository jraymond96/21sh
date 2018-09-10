/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:41:53 by mmerabet          #+#    #+#             */
/*   Updated: 2018/08/06 22:42:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <unistd.h>
# include "ft_printf.h"
# include "get_next_line.h"

void				ft_putchar(char c);
void				ft_putnchar(char c, size_t n);
void				ft_putstr(const char *s);
void				ft_putstrl(const char *s);
void				ft_putnstr(const char *s, size_t n);
void				ft_putendl(const char *s);
void				ft_putnendl(const char *s, size_t n);
void				ft_putnbr(int n);
void				ft_putunbr(unsigned int n);
void				ft_putnbr_base(int n, const char *base);
void				ft_putullong_base(unsigned long long n, const char *base);
void				ft_putptr(void *ptr);
void				ft_putdouble(double n, int precision);

void				ft_putchar_fd(char c, int fd);
void				ft_putnchar_fd(char c, size_t n, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putnstr_fd(const char *s, size_t n, int fd);
void				ft_putnstrl_fd(const char *s, size_t n, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnendl_fd(const char *s, size_t n, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putunbr_fd(unsigned int n, int fd);
void				ft_putnbr_base_fd(int n, const char *base, int fd);
void				ft_putullong_base_fd(unsigned long long n,
									const char *base,
									int fd);
void				ft_putptr_fd(void *ptr, int fd);
void				ft_putdouble_fd(double n, int precision, int fd);

int					ft_getch(void);
int					ft_getwch(void);

#endif
