/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 19:44:38 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 17:30:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

# define OP_ASSOCRL (1 << 0)
# define OP_UNARYL (1 << 1)
# define OP_UNARYLR (1 << 2)
# define OP_BINARY (1 << 3)
# define OP_UNARYLRM (1 << 4)
# define OP_UNARYRM (1 << 5)

typedef struct		s_opt
{
	char			*cur;
	char			**ptr;
	int				n;
	char			c;
	int				seq;
	int				ret;
	char			*clong;
}					t_opt;

typedef enum	e_optret
{
	OPT_END, OPT_UNKNOWN, OPT_ALAST, OPT_OK, OPT_MISSING, OPT_EMPTY, OPT_EQUAL
}				t_optret;

typedef struct		s_strid
{
	char			str[500];
	char			*next;
	int				len;
	int				ifound;
	int				jump;
	int				i;
	int				j;
}					t_strid;

typedef struct s_expf	t_expf;
typedef int			(*t_expfunc)(t_strid *, char **, t_expf *);

typedef struct		s_exp
{
	char			*name;
	t_expfunc		func;
}					t_exp;

struct				s_expf
{
	t_exp			*expansions;
	size_t			len;
	void			*data;
	int				onlyfirst;
};

typedef struct		s_parserf
{
	char			*def_word;
	char			*def_stop;
	char			*def_lstop;
	char			*def_rstop;
	char			*def_hstop;
	t_exp			*exps;
	size_t			exps_len;
	char			*exp_all;
	char			*def_all;
	void			*data;
}					t_parserf;

typedef struct		s_op
{
	char			*name;
	int				t;
}					t_op;

typedef struct		s_lexerf
{
	t_parserf		parserf;
	t_op			*ops;
	size_t			ops_len;
	int				cmd_offset;
	int				op_offset;
	void			*data;
}					t_lexerf;

typedef struct		s_args
{
	int				argc;
	char			**argv;
}					t_args;

typedef struct		s_ast
{
	int				type;
	char			*name;
	char			*cname;
	t_args			*args;
	t_args			*cargs;
	int				assoc;
	int				u;
	int				cmd_offset;
	int				op_offset;
	void			*extra_param;
	void			*data;
	t_lexerf		*lexerf;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_inst
{
	t_args			args;
	char			*delim;
	char			*str;
}					t_inst;

typedef struct s_iterf	t_iterf;

typedef int			(*t_astfunc_cb)(t_ast *, void **, void *, t_iterf *);

typedef struct		s_astfunc
{
	char			*name;
	t_astfunc_cb	func;
	t_astfunc_cb	unary_func;
	int				post;
}					t_astfunc;

struct				s_iterf
{
	t_astfunc		*funcs;
	size_t			funcs_len;
	void			*data;
	int				opmissing_err;
	size_t			bsize;
};

int					exp_var(t_strid *sid, char **res, t_expf *expf);
int					exp_arg(t_strid *sid, char **res, t_expf *expf);
int					exp_tild(t_strid *sid, char **res, t_expf *expf);
int					exp_arth(t_strid *sid, char **res, t_expf *expf);
int					exp_cmd(t_strid *sid, char **res, t_expf *expf);
int					exp_dvar(t_strid *sid, char **res, t_expf *expf);
int					exp_quote(t_strid *sid, char **res, t_expf *expf);
int					exp_cond(t_strid *sid, char **res, t_expf *expf);

int					shell_cmd_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_arth_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_lists_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_andor_seco_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_bckgrnd_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_pipe_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_redir_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_cond_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_else_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_equal_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_hdoc_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);

int					shell_then_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);
int					shell_if_cb(t_ast *ast, void **op, void *res,
								t_iterf *iterf);

int					ft_parser(const char **str, t_args *args, t_parserf *pdef);
void				ft_argsdel(t_args *args);
t_args				*ft_argscopy(t_args *args);

t_ast				*ft_lexer(const char *str, t_lexerf *ldef);
int					ft_astiter(t_ast *ast, void *res, t_iterf *iterf);
void				ft_astdel(t_ast **ast);
void				astdelone(t_ast **ast);
t_ast				*astlink(t_ast *a, t_ast *b, int lr);
t_ast				*newast(t_inst *inst, int type, t_lexerf *ldef, t_ast *cur);
int					ft_astvalid(t_ast *ast);

int					ft_resolver(t_args *args, t_expf *expf);
int					ft_astcresolver(t_ast *ast, t_expf *expf);
int					ft_strexpand(const char *origin,
							char **res,
							int i,
							t_expf *expf);

int					ft_astgood(t_ast *ast);
void				ft_astprint(t_ast *bt, int n);
int					ft_getopt(char ***argv, const char *options, t_opt *opt);
char				**ft_getoptl(char **argv,
							char option,
							const char *loption,
							int lfirst);
char				**ft_getoptv(char **argv, const char *options);

int					ft_interpret(const char *command,
							void *ptr,
							t_lexerf *lexf,
							t_iterf *itf);

#endif
