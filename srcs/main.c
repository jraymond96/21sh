/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/05 01:29:09 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include "ft_printf_ext.h"
#include "ft_btree.h"
#include <unistd.h>
/*
static char		*g_ops[] = {
	DLM_RED, DLM_PIPE, DLM_AOR, DLM_SECO
};
*/

static t_op			g_ops[] = {
	{DLM_REDP, OP_BINARY},
	{"|", OP_BINARY},
	{"&&:||", OP_BINARY},
	{";", OP_BINARY}
};

static t_exp		g_exps[] = {
	{EXP_VAR, exp_var}, {EXP_ARTH, exp_arth}, {EXP_TILD, exp_tild},
	{EXP_CMD, exp_cmd}, {EXP_FARG, exp_farg}
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
		0: auncun enfant; -1: seulement l'enfant droit; 1: seulement l'enfant gauche
		2: les deux, mais d'abord le gauche puie le droit.
		L'utilite: Par exemple pour les operateurs '&& et ||' seulement le fils gauche
		doit etre appele et le fils droit est appelle sous certaine conditions,
		donc on specifie -1. Pour l'exemple on va specifie 2
		Regarde le fichier ft_expr.c pour en voir une vraie utilisation complete
	*/
	{"&&:||", shell_andor_cb, NULL, -1},
	{";", shell_seco_cb, NULL, 2},
	{"|", shell_pipe_cb, NULL, 2},
	{DLM_REDP, NULL, shell_redir_cb, 0}
};

// Structure definissant les pointeurs sur fonctions a appeles a quel moment,
// les fonctions sont dans le fichiers shell_callbacks.c
static t_iterf		g_shell_iterf = {
	// Cette fonction est appele lorsqu'un operande est rencontre, donc une commande
	shell_cmd_cb,
	// Les fonctions qui seront appeles
	g_shell_callbacks, sizeof(g_shell_callbacks) / sizeof(t_astfunc),
	0, 0, sizeof(int)
};

/*
static void	ft_system(char *line)
{
	char		fullpath[1024];
	t_args		args;
	t_shret		shret;
	int			pos;

	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_parser(line, &args, &g_lexerf.parserf)) && g_shell->running)
	{
		ft_resolver(&args, 0);
		if ((pos = ft_strpbrkstr_len(line, g_lexerf.parserf.def_stop)))
			line += pos;
		if (args.argc >= 1
			&& ft_isbuiltin(args.argv[0], &args) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], g_shell->paths, fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", g_shell->name, ft_strshret(shret),
					args.argv[0]);
			else if (ft_exec(fullpath, args.argv, g_shell->envp, &g_shell->curpid) == -1)
				ft_printf("%s: exec format error: %s\n",
						g_shell->name, args.argv[0]);
		}
		ft_argsdel(&args);
	}
	ft_argsdel(&args);
}
*/
static void	printprompt(void)
{
	int	x;

	ft_getcursor(&x, NULL);
	if (x > 1)
		ft_printf("%#{lgrey}%{bold/;0;0;0}%%%{0}\n");
	ft_printf("%{0}%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ", L"㋜",
		g_shell->user, g_shell->pwd, L"∴");
}
//#include <limits.h>
int			main(int argc, char **argv, char **envp)
{
/*	t_exprdata	expr_data;
	EXPRT		res = 0;
	int			efail;
	char		*tmp;

	ft_bzero(&expr_data, sizeof(t_exprdata));
	ft_setenv("A", "0", &expr_data.var_db);
	ft_setenv("B", "10", &expr_data.var_db);
	ft_setenv("LLONG_MAX", (tmp = ft_lltoa(LLONG_MAX)), &expr_data.var_db);
	free(tmp);
	ft_setenv("LLONG_MIN", (tmp = ft_lltoa(LLONG_MIN)), &expr_data.var_db);
	free(tmp);
	ft_setenv("STR", "Hello", &expr_data.var_db);

	envp = expr_data.var_db;
	while (*envp)
		ft_printf("envp before expr: '%s'\n", *envp++);
	ft_printf("\n");
	if ((efail = ft_expr(argv[1], &res, &expr_data, 0, 1, 2, 3)))
		ft_printf("error detected: %d: %s\n", efail, ft_exprerr(efail));
	ft_printf("expr: (%s) = %lld\n\n", argv[1], res);

	envp = expr_data.var_db;
	while (*envp)
		ft_printf("envp after expr: '%s'\n", *envp++);
	ft_delenv(&expr_data.var_db);
	return (0);
*/	char	line[8192];
	int		c;

	shell_begin(argv[0], argc, argv, envp);
	ft_bzero(line, 8192);
	c = 0;
	while (g_shell->running)
	{
		printprompt();
		if ((c = ft_readraw(ft_strclr(line), 8192)))
		{
			if (c == 4 && !(g_shell->running = 0))
				ft_strcpy(ft_strclr(line), "exit");
			if (c != 3)
			{
				ft_printf("executing: '%s'\n", line);
				t_ast	*head = ft_lexer(line, &g_lexerf);
				ft_astprint(head, 0);
				(void)g_shell_iterf;
				ft_printf("\n\n\tIterating the ast:\n\n");
				int	res = 0;
				ft_astiter(head, &res, &g_shell_iterf);
				ft_printf("end res value prout ok bonjour: '%d'\n", res);
				ft_astdel(&head);
				//ft_system(line);
			}
			if (c != 3 && c != 4)
				addhistory(line);
		}
	}
	ft_makeraw(0);
	ft_printf_free_formats();
	return (shell_end());
}
