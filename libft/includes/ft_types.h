/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:41:38 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/23 20:56:59 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

# define FT_HEXM "0123456789ABCDEF"
# define FT_HEX "0123456789abcdef"
# define FT_BIN "01"
# define FT_OCT "01234567"
# define FT_DEC "0123456789"

int					ft_atoi(const char *s);
long				ft_atol(const char *s);
long long			ft_atoll(const char *s);
unsigned int		ft_atoui(const char *s);
unsigned long		ft_atoul(const char *s);
unsigned long long	ft_atoull(const char *s);
double				ft_atod(const char *s);
int					ft_atoi_base(const char *s, const char *base);
int					ft_atoi_basec(const char *s, const char *base);
long long			ft_atoll_base(const char *s, const char *base);

char				*ft_itoa(int n);
char				*ft_ltoa(long n);
char				*ft_lltoa(long long n);
char				*ft_uitoa(unsigned int n);
char				*ft_ultoa(unsigned long n);
char				*ft_ulltoa(unsigned long long n);
char				*ft_dtoa(double n, int precision);
char				*ft_ldtoa(long double n, int precision);
char				*ft_itoa_cbase(int n, const char *base);
char				*ft_uitoa_cbase(unsigned int n, const char *base);
char				*ft_ltoa_cbase(long n, const char *base);
char				*ft_ultoa_cbase(unsigned long n, const char *base);
char				*ft_lltoa_cbase(long long n, const char *base);
char				*ft_ulltoa_cbase(unsigned long long n, const char *base);
char				*ft_tobase(const char *s,
							char *fbase,
							char *tbase);

int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_iscntrl(int c);
int					ft_isspace(int c);
int					ft_ispinct(int c);

int					ft_intlen(int n);
int					ft_longlen(long n);
int					ft_llonglen(long long n);
int					ft_uintlen(unsigned int n);
int					ft_ulonglen(unsigned long n);
int					ft_ullonglen(unsigned long long n);

#endif
