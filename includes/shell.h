/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:39:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/30 21:53:37 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdarg.h>
# include "ft_list.h"

# define DLM_REDP1 "<<:<<*[aA0-zZ9]:>>:*[0-9]>>:<:>:*[<>@=1]&*[0-9]:>&-"
# define DLM_REDP2 DLM_REDP1 ":*[0-9]*[<>@=1]&:*[<>@=1]&:*[0-9]*[<>@=1]&-"
# define DLM_REDP DLM_REDP2 ":*[0-9]*[<>@=1]&*[0-9]:*[0-9]*[<>]"

# define EXP_BRACES "*[{?};(?);\"*\";'*'@b]"
# define EXP_SUBSHELL "*[(?);{?};\"*\";'*'@b]"

# define DLM_WORD " :\t:\n"
# define DLM_HSTOP "&:&&:||:<<:>>:*[<>|;@=1]:>&-:>&"

# define DLM_LSTOP "*[<>@=1]&*[0-9]"
# define DLM_RSTOP1 "*[0-9]*[<>@=1]:*[0-9]*[<>@=1]&-:*[0-9]*[<>@=1]&:*[0-9]>>"
# define DLM_RSTOP DLM_RSTOP1 ":*[0-9]<<"
# define DLM_STOP "while:if:then:else:not:*[0-9]*[<>@=1]&*[0-9]"

# define EXPR_DLM_VARV "*[aA_-zZ_@=1]*[aA0_-zZ9_]:*[aA_-zZ_@=1]"
# define EXPR_DLM_VAR "*[0-9]*[aA_-zZ_]:" EXPR_DLM_VARV
# define EXPR_DLM_EQU "*[+\\-*/%&|^@=1]=:="
# define EXPRT long

# define MAX_BGPROC 21


typedef enum	e_shret
{
	SH_NONE, SH_EXIT, SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_EFAIL,
	SH_ESUCCESS, SH_NDIR, SH_PIPFAIL, SH_DUPFAIL, SH_FORKFAIL, SH_EXECERR,
	SH_MAXBGPROC, SH_NFILE, SH_CONDWTHEN, SH_THENWCOND, SH_ELSEWCOND,
	SH_EXPRERR, SH_MALLOC
	TK_CMD, TK_OP, TK_REDIR, TK_PIPE, TK_ANDOR, TK_SEMICOLON,
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
	EXPR_NOTINT, EXPR_EXPECT, EXPR_PAREXPECT, EXPR_QUOEXPECT, EXPR_OUTRANGE
}				t_exprerr;

typedef int	(*t_builtin_func)(int, char **);

typedef struct		s_builtin
{
	char			*name;
	t_builtin_func	func;
}					t_builtin;

typedef	enum	e_bgstat
{
	BG_RUN, BG_END, BG_KILL, BG_STOP
}				t_bgstat;

typedef struct	s_bgstats
{
	int			status;
	char		*message;
}				t_bgstats;

typedef struct		s_inffork
{
	int				x;
	pid_t			pid;
	char			sign;
	char			status[100];
	char			**cmd;
}					t_inffork;

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
	char			*history_file;
	t_list			*history;
	int				ihis;
	char			*cline;
	t_builtin		*builtins;
	int				dontwait;
	pid_t			curpid;
	int				exitcode;
	t_list			*bgproc;
	pid_t			lpidchange;
	char			*script;
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

/*
** n[0] = length of tld
** n[1] = index of expansion in string USELESS
** n[2] = index of string in argument USELESS
*/

typedef int			(*t_expfunc)(char *, int[3], void *, char **);

typedef struct		s_exp
{
	char			*name;
	t_expfunc		func;
	int				chan;
}					t_exp;

typedef struct		s_expf
{
	t_exp			*expansions;
	size_t			len;
	void			*data;
	int				onlyfirst;
	int				num_chan;
}					t_expf;

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


# define OP_ASSOCRL (1 << 0)
# define OP_UNARYL (1 << 1)
# define OP_UNARYLR (1 << 2)
# define OP_BINARY (1 << 3)
# define OP_UNARYLRM (1 << 4)
# define OP_UNARYRM (1 << 5)

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
	void			*data;
	t_parserf		*parserf;
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

typedef struct		s_redir
{
	int				type;
	int				fd_out;
	int				fd_in;
	int				replace_fd;
	t_args			*names;
	char			*str;
	char			*file;
}					t_redir;

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

int					exp_var(char *tld, int n[3], void *data, char **res);
int					exp_tild(char *tld, int n[3], void *data, char **res);
int					exp_arth(char *tld, int n[3], void *data, char **res);
int					exp_cmd(char *tld, int n[3], void *data, char **res);
int					exp_farg(char *tld, int n[3], void *data, char **res);
int					exp_cond(char *tld, int n[3], void *data, char **res);
int					exp_bslash(char *tld, int n[3], void *data, char **res);

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

int					ft_parser(const char **str, t_args *args, t_parserf *pdef);
void				ft_argsdel(t_args *args);
t_args				*ft_argscopy(t_args *args);

t_ast				*ft_lexer(const char *str, t_lexerf *ldef);
int					ft_astiter(t_ast *ast, void *res, t_iterf *iterf);
void				ft_astdel(t_ast **ast);
void				astdelone(t_ast **ast);
t_ast				*astlink(t_ast *a, t_ast *b, int lr);
t_ast				*newast(t_inst *inst, int type, t_lexerf *ldef, t_ast *cur);

int					ft_resolver(t_args *args, t_expf *expf);
int					ft_astresolver(t_ast *ast, t_expf *expf);
int					ft_astcresolver(t_ast *ast, t_expf *expf);
int					ft_strexpand(const char *origin,
							char **res,
							int i,
							t_expf *expf);

int					ft_astgood(t_ast *ast);
void				ft_astprint(t_ast *bt, int n);
t_list				*list_redirections(t_ast **ast, t_expf *expf);

char				*typestr(int type);

char				*ft_getenv(char *name, char **envp);
int					ft_modenv(char *str, char ***envp);
int					ft_setenv(char *name, char *value, char ***envp);
int					ft_unsetenv(char *name, char ***envp);
int					ft_putenv(char *name, char *value, char ***envp);
char				**ft_copyenv(char **envp);
char				**ft_mergeenv(char ***a, char **b);
void				ft_delenv(char ***envp);

void				printprompt(int i);
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

int					ft_getfullpath(char *fname,
									char **paths,
									char *fullpath,
									size_t size);

char				*ft_strshret(int shret);
int					ft_printshret(int shret, char *name);

int					shell_begin(char *name, int argc, char **argv, char **envp);
int					shell_end(void);
int					shell_init(int argc, char **argv);

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
int					builtin_return(int argc, char **argv);
int					builtin_true(int argc, char **argv);
int					builtin_false(int argc, char **argv);
int					builtin_jobs(int argc, char **argv);
int					builtin_fg(int argc, char **argv);

extern int			g_dontfree;
extern t_shell		*g_shell;

typedef int			(*t_funcdef_cb)(char *, char *);

typedef struct		s_funcdef
{
	char			*name;
	t_funcdef_cb	*func;
}					t_funcdef;

typedef struct		s_exprdata
{
	char			***var_db;
	char			**var_db2;
	t_funcdef		*func_db;
	va_list			vp;
	int				vp_limit;
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

int		exec_cmd_background(t_ast *ast, void *res, t_iterf *iterf);
int		exec_bltin_bin(t_ast *ast, void *res, t_iterf *iterf);
int		handle_bgstat(pid_t pid, int status);
int		handle_bgproc(pid_t pid_fork, char **cmd);
void	check_bgend(void);
int		end_status(char *str);
int		deli_shiftend(int del, int size);
void	print_cmd_args(char **tab);
void	print_cmd_args2(char **tab);
char	**ret_args(t_ast *ast);
t_ast	**ret_astargs(t_ast *ast);

#endif
