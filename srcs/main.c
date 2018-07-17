/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/17 21:29:40 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include "ft_math.h"
#include "ft_printf_ext.h"
#include "ft_btree.h"
#include <unistd.h>
#include <limits.h>

static t_op			g_ops[] = {
	{DLM_REDP, OP_BINARY},
	{"not", OP_UNARYL},
	{"&", OP_BINARY | OP_ASSOCRL},
	{"|", OP_BINARY},
	{"&&:||", OP_BINARY},
	{"if", OP_UNARYL},
	{"then", OP_BINARY},
	{"else", OP_BINARY},
	{";", OP_BINARY}
};

static t_exp		g_exps[] = {
	{"$*[aA0_-zZ9_]:$?", exp_var, 0},
	{"*[$((*));\"*\";'*'@b]", exp_arth, 0},
	{"~:~+:~-", exp_tild, 1},
	{"\033~", exp_bslash, 1},
	{"\\\\*[@=1]", exp_bslash, 0},
	{"*[`?`;\";';$'?'@b]", exp_cmd, 0},
	{"*[\"*\"@b]:'*':$'*'", exp_farg, 0},
	{"*[\"'@=1]*[@>0]:$'*[@>0]:\":':$'", exp_farg, 0},
	{"*[$\\[*\\];\"*\";'*'@b]", exp_cond, 0}
};

static t_expf		g_expf = {
	g_exps, sizeof(g_exps), NULL, 0, 2
};

static t_lexerf		g_lexerf = {
	{
		DLM_WORD, DLM_STOP, DLM_HSTOP, g_exps, sizeof(g_exps) / sizeof(t_exp),
		NULL, NULL, NULL
	}, g_ops, sizeof(g_ops) / sizeof(t_op), TK_CMD, TK_OP, NULL
};

static t_astfunc	g_shell_callbacks[] = {
	/*
		Si l'operateur correspond au regex alors la fonction sera appelee
		Si l'operateur est indique comme unaire alors c'est le deuxieme pointeur
		sur fonction qui est appele.
		Le dernier attribut permet de preciser manuellement qu'elle enfant
		appelle :
		0: auncun enfant; -1: seulement l'enfant gauche; 1: seulement l'enfant droit
		2: les deux, mais d'abord le gauche puie le droit.
		L'utilite: Par exemple pour les operateurs '&& et ||' seulement le fils gauche
		doit etre appele et le fils droit est appelle sous certaine conditions,
		donc on specifie -1. Pour l'exemple on va specifie 2
		Regarde le fichier ft_expr.c pour en voir une vraie utilisation complete
	*/
	{"*[$\\[*\\];\"*\";'*'@b]", shell_arth_cb, NULL, 3},
	{"", shell_cmd_cb, NULL, 3},
	{"if:then", NULL, shell_cond_cb, 0},
	{"else:not", shell_else_cb, shell_else_cb, -1},
	{"&&:||", shell_andor_cb, NULL, -1},
	{"&", NULL, shell_bckgrnd_cb, 0},
	{";", NULL, NULL, 2},
	{"|", NULL, shell_pipe_cb, 0},
	{DLM_REDP, NULL, shell_redir_cb, 0},
};

// Structure definissant les pointeurs sur fonctions a appeles a quel moment,
// les fonctions sont dans le fichiers shell_callbacks.c
static t_iterf		g_shell_iterf = {
	// Les fonctions qui seront appeles
	g_shell_callbacks, sizeof(g_shell_callbacks) / sizeof(t_astfunc),
	(void *)&g_expf, 0, sizeof(int)
};

void	printprompt(int i)
{
	int	x;

	if (i)
	{
		ft_getcursor(&x, NULL);
		if (x > 1)
			ft_printf("%{invert}%%%{0}\n");
	}
	ft_printf("%{0}%{bold}%S%{0} %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ",
			L"㋜", g_shell->user, g_shell->pwd, L"∴");
}

int			main(int argc, char **argv, char **envp)
{
/*	char	*res = NULL;
	int		err;

	shell_begin("21sh", argc, argv, envp);
	ft_printf("expansion: '%s'\n", argv[1]);
	if ((err = ft_strexpand(argv[1], &res, 0, &g_expf)))
		ft_printf("err: %d\n", err);
	ft_printf("'%s' -> '%s'\n", argv[1], res);
	free(res);
	return (0);
	t_exprdata	expr_data;
	EXPRT		res = 0;
	int			efail;
	char		*tmp;
	char		**var_db;

	ft_bzero(&expr_data, sizeof(t_exprdata));
	expr_data.vp_limit = 5;
	var_db = NULL;
	expr_data.var_db = &var_db;
	ft_setenv("A", "0", expr_data.var_db);
	ft_setenv("B", "10", expr_data.var_db);
	ft_setenv("LLONG_MAX", (tmp = ft_lltoa(LLONG_MAX)), expr_data.var_db);
	free(tmp);
	ft_setenv("LLONG_MIN", (tmp = ft_lltoa(LLONG_MIN)), expr_data.var_db);
	free(tmp);
	ft_setenv("STR", "Hello", expr_data.var_db);

	envp = *expr_data.var_db;
	while (*envp)
		ft_printf("envp before expr: '%s'\n", *envp++);
	ft_printf("\n");
	if ((efail = ft_expr(argv[1], &res, &expr_data, 0, 1, 2, 3, 4)))
		ft_printf("error detected: %d: %s\n", efail, ft_exprerr(efail));
	ft_printf("expr: (%s) = %lld\n\n", argv[1], res);
	envp = *expr_data.var_db;
	while (*envp)
		ft_printf("envp after expr: '%s'\n", *envp++);
	ft_delenv(expr_data.var_db);
	return (0);
*/	char	line[8192];
	int		c;

	shell_begin("21sh", argc, argv, envp);
//	ft_bzero(g_shell->bgproc, (sizeof(t_inffork *) * MAX_BGPROC)); // bzero pour le tableau de proc en backgrd
	ft_bzero(line, 8192);
	c = 0;
	while (g_shell->running)
	{
		printprompt(1);
		if ((c = ft_readraw(ft_strclr(line), 8192)))
		{
			if (c == 4 && !(g_shell->running = 0))
				ft_strcpy(ft_strclr(line), "exit");
			if (c != 3)
			{
				t_ast	*head = ft_lexer(line, &g_lexerf);
//				ft_astprint(head, 0);
				(void)g_shell_iterf;
				if ((c = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
					ft_printf("21sh: %s: [%s]\n", ft_strshret(c), line,
							(g_shell->exitcode = 1));
				int	x = -1;
				while (++x < (MAX_BGPROC - 1))
				{
					if (g_shell->bgproc[x])
						ft_printf("pid: %d status: %s nb: %d\n",
									g_shell->bgproc[x]->pid,
									g_shell->bgproc[x]->status,
									g_shell->bgproc[x]->x);
				}
				check_bg();
				ft_astdel(&head);
			}
			if (c != 3 && c != 4)
				addhistory(line);
		}
	}
	ft_makeraw(0);
	ft_printf_free_formats();
	return (shell_end());
}
