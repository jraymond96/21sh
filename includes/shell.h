/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:39:46 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/24 20:35:46 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdarg.h>
# include "ft_list.h"
# include "readraw.h"
# include "parser.h"
# include "expr.h"
# include "job_control.h"

# define DLM_REDP1 "<<:<<<:*[0-9]<<<:<:>:*[0-9]<<:>>:*[0-9]>>:*[<>@=1]&*[0-9]"
# define DLM_REDP2 DLM_REDP1 ":*[<>@=1]&-:*[0-9]*[<>@=1]&:*[0-9]*[<>@=1]&-"
# define DLM_REDP DLM_REDP2 ":*[<>@=1]&:*[0-9]*[<>@=1]&*[0-9]:*[0-9]*[<>]"

# define EXP_BRACES "*[{?};(?);\"*\";'*'@b]"
# define EXP_SUBSHELL "*[(?);{?};\"*\";'*'@b]"

# define DLM_WORD " :\t:\n:#*\n:#*[@>0]"
# define DLM_HSTOP "&&:||:<<:>>:*[<>@=1]&-:*[<>@=1]&:*[<>|&;,!@=1]:\\:="
# define DLM_WORD_N " :\t:#*\n:#*[@>0]"
# define DLM_HSTOP_N "\n:&&:||:<<:>>:*[<>@=1]&-:*[<>@=1]&:*[<>&|;,!@=1]:\\:="

# define DLM_LSTOP "*[<>@=1]&*[0-9]"
# define DLM_RSTOP1 "*[0-9]*[<>@=1]:*[0-9]*[<>@=1]&-:*[0-9]*[<>@=1]&:*[0-9]>>"
# define DLM_RSTOP DLM_RSTOP1 ":*[0-9]<<"
# define DLM_STOP "while:if:then:else:not:*[0-9]*[<>@=1]&*[0-9]"

# define HDOC_TMP_FILE "/tmp/.21sh-hdoc.tmp"

typedef enum	e_shret
{
	SH_NONE, SH_EXIT, SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_EFAIL,
	SH_ESUCCESS, SH_NDIR, SH_PIPFAIL, SH_DUPFAIL, SH_FORKFAIL, SH_EXECERR,
	SH_MAXBGPROC, SH_NFILE, SH_CONDWTHEN, SH_THENWCOND, SH_ELSEWCOND,
	SH_HDOCWFAIL, SH_HDOCRFAIL, SH_HDOCWORD, SH_HDOCSTOP, SH_OPENFILE,
	SH_CMDERR, SH_NHOME, SH_NOLDPWD, SH_BADFD, SH_MALLOC, SH_BADEXPR,
	SH_EXPRERR, TK_CMD, TK_OP, TK_EQUAL, TK_REDIR, TK_PIPE, TK_ANDOR,
	TK_SEMICOLON, TK_LEFT, TK_RIGHT, TK_LLEFT, TK_LRIGHT
}				t_shret;

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

typedef struct		s_allf
{
	t_parserf		*parserf;
	t_lexerf		*lexerf;
	t_iterf			*iterf;
	t_expf			*expf;
}					t_allf;

typedef struct		s_redir
{
	int				type;
	int				fda;
	int				fdb;
	int				fdz;
	int				checked;
	int				rep;
	t_args			*names;
	char			*str;
	char			*file;
}					t_redir;

typedef struct		s_func
{
	char			*name;
	char			*src;
	t_ast			*ast;
}					t_func;

typedef struct		s_shell
{
	char			*name;
	char			pwd[2048];
	char			*homepwd;
	char			*user;
	char			**paths;
	char			**envp;
	int				running:1;
	char			*history_file;
	int				exitcode;
	char			*script;
	char			*start_cmd;
	int				kill_builtin;
	int				width;
	int				height;
	int				bits;
	short			numproc;
	t_list			*funcs;
	t_allf			*allf;
	t_list			*history;
	t_args			*curargs;
	t_list			*bgproc;
	t_list			*lstmodif_pid;
	pid_t			curpid;
	pid_t			shellpid;
}					t_shell;

void				printprompt(int i);
t_func				*get_function(char *name);
int					check_function(t_ast *ast, void *res, t_iterf *iterf);
void				redir_printerror(t_redir *r, int err, void **op);
int					repair_hdoc(t_ast *ast, int n);
int					check_syntax(t_ast *ast, t_expf *expf);
int					replace_fd(t_redir *r, int *closed_fd);
t_list				*list_redirections(t_ast **ast, t_expf *expf);

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
void				ft_getsize(int *lns, int *cols);
char				*ft_parsepath(char *target, char *origin, size_t size);

void				ft_makeraw(int setb);
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
void				init_gshell(char **envp, char *name);

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
int					builtin_function(int argc, char **argv);
int					builtin_source(int argc, char **argv);
int					builtin_true(int argc, char **argv);
int					builtin_false(int argc, char **argv);
int					builtin_jobs(int argc, char **argv);
int					builtin_fg(int argc, char **argv);
int					builtin_bg(int argc, char **argv);

extern int			g_dontfree;
extern t_shell		*g_shell;
extern t_allf		g_allf;

#endif
