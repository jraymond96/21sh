/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:42:15 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/16 22:34:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_H
# define FT_STR_H

# include <stdlib.h>
# include <wctype.h>
# include <stdarg.h>

size_t				ft_strlen(const char *s);
size_t				ft_strlenl(const char *s);
size_t				ft_strlenk(const char *s);
size_t				ft_strlenli(const char *s);
char				*ft_strend(const char *str);

char				*ft_strdup(const char *s);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strmdup(const char *s, size_t n);

char				*ft_strdupl(const char *s);
char				*ft_strndupl(const char *s, size_t n);
char				*ft_strdupk(const char *s);
char				*ft_strndupk(const char *s, size_t n);
char				*ft_strdupli(const char *s);
char				*ft_strndupli(const char *s, size_t n);

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);

char				*ft_strcat(char *a, const char *b);
char				*ft_strcatc(char *a, char b);
char				*ft_strncat(char *a, const char *b, size_t n);
char				*ft_strcatl(char *a, const char *b);
char				*ft_strncatl(char *a, const char *b, size_t n);
size_t				ft_strlcat(char *a, const char *b, size_t n);

char				*ft_strchr(const char *s, int c);
char				*ft_strchrl(const char *s, int c);
char				*ft_strchrln(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *a, const char *b);
char				*ft_strnstr(const char *a, const char *b, size_t n);
char				*ft_strpbrk(const char *s, const char *charset);
int					ft_strpbrk_pos(const char *s, const char *charset);
int					ft_strnrpbrk_pos(const char *s,
								const char *charset,
								size_t n);
int					ft_strpbrkl_pos(const char *s, const char *charset);
char				*ft_strpbrkl(const char *s, const char *charset);
int					ft_strnpbrkl_pos(const char *s,
								const char *charset,
								size_t n);
char				*ft_strnpbrkl(const char *s,
								const char *charset,
								size_t n);

int					ft_strpbrkstr_len(const char *a, const char *strset);
int					ft_strpbrkstrl_len(const char *a, const char *strset);
int					ft_strpbrkstr_pos(const char *a, const char *strset);
int					ft_strpbrkstrl_pos(const char *a, const char *strset);
int					ft_strnpbrkstr_len(const char *a, const char *strset,
									int n);
int					ft_strnpbrkstrl_len(const char *a, const char *strset,
									int n);
int					ft_strnpbrkstr_pos(const char *a, const char *strset,
									int n);
int					ft_strnpbrkstrl_pos(const char *a, const char *strset,
									int n);
int					ft_strpbrkstrp_len(const char *a,
									int type,
									size_t size,
									...);
int					ft_strpbrkstrpl_len(const char *a,
									int type,
									size_t size,
									...);
int					ft_strpbrkstrpv_len(const char *a,
									int type,
									size_t size,
									va_list vp);
int					ft_strpbrkstrplv_len(const char *a,
									int type,
									size_t size,
									va_list vp);
int					ft_strpbrkstrp_pos(const char *a,
									int type,
									size_t size,
									...);
int					ft_strpbrkstrpl_pos(const char *a,
									int type,
									size_t size,
									...);

int					ft_strcmp(const char *a, const char *b);
int					ft_strncmp(const char *a, const char *b, size_t n);

int					ft_strequ(const char *a, const char *b);
int					ft_strequl(const char *a, const char *b);
int					ft_strnequl(const char *a, const char *b, size_t n);
int					ft_strequ_x(const char *a, const char *strset);

char				*ft_strnchr(const char *s, int c, size_t n);
char				*ft_strnchrl(const char *s, int c, size_t n);
char				*ft_strnchrln(const char *s, int c, size_t n);
int					ft_strnchrl_pos(const char *s, int c, size_t n);
int					ft_strnchrln_pos(const char *s, int c, size_t n);
char				*ft_strnrchr(const char *s, int c, size_t n);
int					ft_strnrchr_pos(const char *s, int c, size_t n);
int					ft_strrchr_pos(const char *s, int c);
char				*ft_strrstr(const char *a, const char *b);
char				*ft_strnrstr(const char *a, const char *b, size_t n);
int					ft_strchr_pos(const char *a, int b);
int					ft_strchrl_pos(const char *a, int b);
int					ft_strstr_pos(const char *a, const char *b);
int					ft_strstrl_pos(const char *a, const char *b);

char				*ft_strrepeat(const char *s, int n);
char				*ft_strrepeat_clr(char *s, int n);

char				*ft_revstr(char *a);
char				*ft_revnstr(char *a, size_t n);
void				ft_swap(char *a, char *b);
int					ft_strforeach(const char *s, int (*f)(char c));

char				*ft_strnew(size_t size);
void				ft_strdel(char **ap);
char				*ft_strclr(char *s);
char				*ft_strnclr(char *s, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char *s, char (*f)(char));
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
int					ft_strequ(const char *a, const char *b);
int					ft_strnequ(const char *a, const char *b, size_t n);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
char				*ft_strtrim(const char *s);
char				*ft_strtrim_clr(char *s);
char				**ft_strsplit(const char *s, char sep);
char				**ft_strsplitstr(const char *s, const char *sep);
size_t				ft_tabsize(char **tab);
int					ft_strcount(const char *s, char a);
int					ft_strcountstr(const char *s, const char *a);
char				*ft_strrep(const char *s, char a, char b);
char				*ft_strrepc(char *s, char a, char b);
char				*ft_strrepstr(const char *s, const char *a, const char *b);
char				*ft_strrep_clr(char *s, char a, char b);
char				*ft_strrepstr_clr(char *s, const char *a, const char *b);
char				*ft_strafterstr(const char *s, const char *a);
char				*ft_strafter(const char *s, char a);
char				*ft_strbeforestr(const char *s, const char *a);
char				*ft_strbefore(const char *s, char a);
char				*ft_strbetween(const char *s, char a, char b);
char				*ft_strbetweenl(const char *s, char a, char b);
char				*ft_strbetweenstr(const char *s,
									const char *a,
									const char *b);
int					ft_strbetweenps(char **s, const char *a, const char *b);
char				*ft_strbetweenstr_ext(const char *s,
									const char *ext);
int					ft_strbetweenps_ext(char **s, const char *ext);

char				*ft_strjoin(const char *a, const char *b);
char				*ft_strnjoin(const char *a, const char *b, size_t n);
char				*ft_strjoinc(const char *a, char b);
char				*ft_strjoincs(char a, const char *b);
char				*ft_strnjoin_clr(char *a, char *b, size_t n, int d);
char				*ft_strjoin_clr(char *a, char *b, int d);
char				*ft_strjoinc_clr(char *a, char b);
char				*ft_strjoincs_clr(char a, char *b);
char				*ft_strjoinl(const char *a, const char *b);
char				*ft_strnjoinl(const char *a, const char *b, size_t n);
char				*ft_strjoinl_clr(char *a, char *b, int d);
char				*ft_strnjoinl_clr(char *a, char *b, size_t n, int d);

typedef struct		s_pairint
{
	char			*ext;
	char			*a;
	char			*b;
	int				len;
	int				la;
	int				lb;
	char			tmp;
}					t_pairint;

typedef struct		s_mchi
{
	char			*str;
	int				type;
	int				len;
	int				t;
	int				whatever;
	int				level;
	struct s_mchi	*next;
}					t_mchi;

# define RGX_END 1
# define RGX_BKSLSH 2
# define RGX_N 4

extern int			g_iread;
extern int			g_explicitlev;
extern int			g_ifound;

t_mchi				*ft_getmchi(const char *match);
void				ft_delmchi(t_mchi *head);

int					ft_strmatch_old(const char *str, const char *match);
int					ft_strmatch(const char *str, const char *match);
int					ft_strmatchl(const char *str, const char *match);
int					ft_strmatch_x(const char *a, const char *strset);

int					ft_strnmatch(const char *str, const char *match, int n);
int					ft_strnmatchl(const char *str, const char *match, int n);

int					ft_strmatch_opt(const char *str,
							const char *match,
							int option);
int					ft_strnmatch_opt(const char *str,
							const char *match,
							int n,
							int option);

int					ft_strtks(const char *str, t_mchi *tks, int option);
int					ft_strntks(const char *str,
							t_mchi *tks,
							int n,
							int option);

int					checkwild3(const char **str,
							t_mchi *cur,
							t_mchi *nxt,
							int n);

int					ft_wcharlen(wchar_t wc);
char				*ft_getwchar(wchar_t wc);
int					ft_wstrlen(const wchar_t *wcs);
int					ft_wstrnlen(const wchar_t *wcs, int n);
char				*ft_getwstr(const wchar_t *wcs);
char				*ft_getnwstr(const wchar_t *wc, int n);

#endif
