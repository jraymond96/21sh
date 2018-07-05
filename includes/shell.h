/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:39:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/05 04:39:25 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdarg.h>
# include "ft_list.h"

# define DLM_REDS "<<:>>:*[0-9]>>:<:>"
# define DLM_REDP DLM_REDS ":*[0-9]*[<>@=1]&-:*[0-9]*[<>@=1]&*[0-9]:*[0-9]*[<>]"
# define DLM_REDT "<<:>>:*[<>@=1]&:<:>"

# define EXP_VAR "$*[aA0_-zZ9_]"
# define EXP_CMD "*[`?`;\";';$'*'@b]"
# define EXP_FARG "\"*\":'*':$'*'"
# define EXP_ARTH "$((*))"
# define EXP_TILD "~"

# define DLM_WORD " :\t"
# define DLM_HSTOP "&&:||:<<:>>:*[<>|;@=1]"
# define DLM_STOP1 "*[0-9]>>:*[0-9]*[<>@=1]&*[0-9]"
# define DLM_STOP DLM_STOP1 ":*[0-9]*[<>@=1]&-:*[0-9]*[<>@=1]"

# define EXPR_DLM_VARV "*[aA_-zZ_@=1]*[aA0_-zZ9_]:*[aA_-zZ_@=1]"
# define EXPR_DLM_VAR "*[0-9]*[aA_-zZ_]:" EXPR_DLM_VARV
# define EXPR_DLM_EQU "*[+\\-*/%&|^@=1]=:="
# define EXPRT long long

typedef enum	e_shret
{
	SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_NONE, SH_EFAIL, SH_ESUCCESS,
	SH_NDIR, TK_CMD, TK_OP, TK_REDIR, TK_PIPE, TK_ANDOR, TK_SEMICOLON,
	TK_LEFT, TK_RIGHT, TK_LLEFT, TK_LRIGHT
}				t_shret;

typedef enum	e_optret
{
	OPT_END, OPT_UNKNOWN, OPT_ALAST, OPT_OK, OPT_MISSING, OPT_EMPTY, OPT_EQUAL
}				t_optret;

typedef enum	e_exprerr
{
	EXPR_OK, EXPR_MEMERR, EXPR_NCLOSEPAR, EXPR_BADEXPR, EXPR_UNKFUNC,
	EXPR_UNKVAR, EXPR_DIVZERO, EXPR_LVALREQ, EXPR_OPMISS, EXPR_OPTMISS,
	EXPR_NOTINT, EXPR_EXPECT
}				t_exprerr;

typedef int	(*t_builtin_func)(int, char **);

typedef struct		s_builtin
{
	char			*name;
	t_builtin_func	func;
}					t_builtin;

typedef struct		s_shell
{
	char			*name;
	char			pwd[2048];
	char			*homepwd;
	char			*user;
	char			**paths;
	char			**envp;
	int				running:1;
	int				hisfd;
	t_list			*history;
	int				ihis;
	char			*cline;
	t_builtin		*builtins;
	pid_t			curpid;
	int				exitcode;
}					t_shell;

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

typedef int			(*t_expfunc)(char *, int[3], void *, char **);

typedef struct		s_exp
{
	char			*name;
	t_expfunc		func;
}					t_exp;

typedef struct		s_args
{
	int				argc;
	char			**argv;
	t_exp			*exps;
	size_t			exps_len;
	void			*data;
	char			*exp_all;
}					t_args;

typedef struct		s_ast
{
	int				type;
	char			*name;
	t_args			*args;
	int				assoc;
	int				u;
	int				cmd_offset;
	int				op_offset;
	void			*data;
	struct s_ast	*parent;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

typedef struct		s_inst
{
	t_args			args;
	char			*delim;
}					t_inst;

typedef struct		s_rdrctn
{
	int				type;
	int				fd_out;
	int				fd_in;
	t_args			*names;
	char			*str;
}					t_rdrctn;

typedef struct		s_parserf
{
	char			*def_word;
	char			*def_stop;
	char			*def_hstop;
	t_exp			*exps;
	size_t			exps_len;
	char			*_exp_all;
	char			*_def_all;
	void			*data;
}					t_parserf;

# define OP_ASSOCRL (1 << 0)
# define OP_UNARYL (1 << 1)
# define OP_UNARYLR (1 << 2)
# define OP_BINARY (1 << 3)
# define OP_UNARYLRM (1 << 4)

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

typedef struct		s_iterf t_iterf;

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
	t_astfunc_cb	op_func;
	t_astfunc		*funcs;
	size_t			funcs_len;
	int				resolve_first;
	int				opmissing_err;
	size_t			bsize;
};

int					exp_var(char *tld, int n[3], void *data, char **res);
int					exp_tild(char *tld, int n[3], void *data, char **res);
int					exp_arth(char *tld, int n[3], void *data, char **res);
int					exp_cmd(char *tld, int n[3], void *data, char **res);
int					exp_farg(char *tld, int n[3], void *data, char **res);

int					shell_cmd_cb(t_ast *ast, void **op, void *res, t_iterf *);
int					shell_andor_cb(t_ast *ast, void **op, void *res,
								t_iterf *);
int					shell_seco_cb(t_ast *ast, void **op, void *res, t_iterf *);
int					shell_pipe_cb(t_ast *ast, void **op, void *res, t_iterf *);
int					shell_redir_cb(t_ast *ast, void **op, void *res,
								t_iterf *);

char				*ft_parser(const char *str, t_args *args, t_parserf *pdef);
void				ft_argsdel(t_args *args);

t_ast				*ft_lexer(const char *str, t_lexerf *ldef);
int					ft_astiter(t_ast *ast, void *res, t_iterf *iterf);
void				ft_astdel(t_ast **ast);
void				astdelone(t_ast **ast);
t_ast				*astlink(t_ast *a, t_ast *b, int lr);

int					ft_resolver(t_args *args,
							int onlyfirst);
int					ft_astresolver(t_ast *ast,
							int onlyfirst);

int					ft_astgood(t_ast *ast);
void				ft_astprint(t_ast *bt, int n);
t_list				*list_redirections(t_ast **ast);

char				*typestr(int type);

char				*ft_getenv(char *name, char **envp);
int					ft_modenv(char *str, char ***envp);
int					ft_setenv(char *name, char *value, char ***envp);
int					ft_unsetenv(char *name, char ***envp);
int					ft_putenv(char *name, char *value, char ***envp);
char				**ft_copyenv(char **envp);
char				**ft_mergeenv(char ***a, char **b);
void				ft_delenv(char ***envp);

int					ft_access(char *filename, int tests);
int					ft_chdir(char *target, char *pwd, size_t size, int slink);
int					ft_chdirl(char *target, char *pwd, size_t size);
char				*ft_getcwd(char *pwd, size_t size);
void				ft_getcursor(int *x, int *y);
int					ft_getopt(char ***argv, const char *options, t_opt *opt);
char				**ft_getoptl(char **argv,
							char option,
							const char *loption,
							int lfirst);
char				**ft_getoptv(char **argv, const char *options);
char				*ft_parsepath(char *target, char *origin, size_t size);

void				ft_makeraw(int setb);
int					ft_readraw(char *line, size_t size);

char				**ft_getpaths(char **envp);
void				resetpath(void);

int					ft_getfullpath(char *fname, char **paths, char *fullpath,
									size_t size);

char				*ft_strshret(t_shret shret);

void				shell_begin(char *name, int argc, char **argv, char **envp);
int					shell_end(void);
void				shell_init(int argc, char **argv);

void				addhistory(char *line);
char				*gethistory(int i);
void				clearhistory(int save);
void				movehistory(char c, char *line, size_t *cursor);

int					ft_exec(char *name, char **argv, char **envp, pid_t *pid);

t_shret				ft_isbuiltin(char *name, t_args *args);
int					isbuiltin(char *name);
int					execbuiltin(char *name, t_args *args);

int					builtin_cd(int argc, char **argv);
int					builtin_env(int argc, char **argv);
int					builtin_echo(int argc, char **argv);
int					builtin_exit(int argc, char **argv);
int					builtin_setenv(int argc, char **argv);
int					builtin_unsetenv(int argc, char **argv);
int					builtin_printenv(int argc, char **argv);
int					builtin_history(int argc, char **argv);
int					builtin_pwd(int argc, char **argv);

extern int			g_dontfree;
extern t_shell		*g_shell;
extern int			g_exprerr;
extern char			*g_exprstr;

typedef int			(*t_funcdef_cb)(char *, char *);

typedef struct		s_funcdef
{
	char			*name;
	t_funcdef_cb	*func;
}					t_funcdef;

typedef struct		s_exprdata
{
	char			**var_db;
	char			**var_db2;
	t_funcdef		*func_db;
	va_list			vp;
	int				expr_lvl;
}					t_exprdata;

char				*ft_exprerr(int efail);
int					ft_expr(const char *expr,
						EXPRT *res,
						t_exprdata *data,
						...);
int					ft_vexpr(const char *expr,
						EXPRT *res,
						t_exprdata *data,
						va_list vp);
int					ft_ast_iter(t_ast *ast, t_exprdata *data);

int					expr_parenthesis(char *tld, int n[3], t_exprdata *data,
									char **res);
int					expr_function(char *tld, int n[3], t_exprdata *data,
									char **res);
int					expr_parameter(char *tld, int n[3], t_exprdata *data,
									char **res);
int					expr_variable(char *tld, int n[3], t_exprdata *data,
									char **res);
int					expr_unarys(char *tld, int n[3], t_exprdata *data,
									char **res);

int					expr_unary_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_incdec_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_arth_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_comp_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_cond_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_equ_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_tern_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);

#endif