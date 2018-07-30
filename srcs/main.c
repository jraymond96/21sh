/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/26 16:43:06 by mmerabet         ###   ########.fr       */
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
#include <fcntl.h>

static t_op			g_ops[] = {
	{DLM_REDP, OP_BINARY},
	{"not", OP_UNARYL},
	{"&", OP_BINARY | OP_ASSOCRL},
	{"|", OP_BINARY},
	{"&&:||", OP_BINARY},
	{"if:while", OP_UNARYL},
	{"then", OP_BINARY},
	{"else", OP_BINARY},
	{";", OP_BINARY}
};

static t_exp		g_exps[] = {
	{"\\\\*[@=1]", exp_bslash, 0},
	{"$*[aA0_-zZ9_]:$?", exp_var, 0},
	{"*[$((*));\"*\";'*'@b]", exp_arth, 0},
	{"~:~+:~-", exp_tild, 1},
//	{"\033~", exp_bslash, 1},
	{"*[`?`;\";';$'?'@b]", exp_cmd, 0},
	{"*[\"*\"@b]:'*':$'*'", exp_farg, 0},
	{"*[\"'@=1]*[@>0]:$'*[@>0]:\":':$'", exp_farg, 0},
	{"*[$\\[*\\];\"*\";'*'@b]", exp_cond, 0},

	{EXP_BRACES, NULL, 0},
	{EXP_SUBSHELL, NULL, 0}
};

static t_expf		g_expf = {
	g_exps, sizeof(g_exps), NULL, 0, 2
};

static t_lexerf		g_lexerf = {
	{
		DLM_WORD, DLM_STOP, DLM_LSTOP, DLM_RSTOP, DLM_HSTOP,
		g_exps, sizeof(g_exps) / sizeof(t_exp), NULL, NULL, NULL
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
		donc on specifie -1.
	*/
	{EXP_BRACES, shell_lists_cb, NULL, 3},
	{EXP_SUBSHELL, shell_lists_cb, NULL, 3},
	{"*[$\\[*\\];\"*\";'*'@b]", shell_arth_cb, NULL, 3},
	{"", shell_cmd_cb, NULL, 3},
	{"if:then", NULL, shell_cond_cb, 0},
	{"else:not", shell_else_cb, shell_else_cb, -1},
	{"&&:||", shell_andor_seco_cb, NULL, -1},
	{"&", NULL, shell_bckgrnd_cb, 0},
	{";", NULL, shell_andor_seco_cb, 2},
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
	int		x;
	char	*start_pwd;

	if (i)
	{
		ft_getcursor(&x, NULL);
		if (x > 1)
			ft_printf("%{0}%{invert}%%%{0}\n");
	}
	start_pwd = NULL;
	if (ft_strstr_pos(g_shell->pwd, g_shell->homepwd) == 0)
		start_pwd = g_shell->pwd + ft_strlen(g_shell->homepwd);
	ft_printf("%{0}%{bold}%S%{0} %{lred}%s %{lcyan}%s%s%{0} %{bold}%S%{0} ",
			L"㋜", g_shell->user, (start_pwd ? "~" : ""),
			(start_pwd ? start_pwd : g_shell->pwd), L"∴");
}

int			main(int argc, char **argv, char **envp)
{
	t_ast	*head;
	char	line[8192];
	int		c;
	
	shell_begin(argv[0], argc, argv, envp);
	if (g_shell->script)
	{
		head = ft_lexer(g_shell->script, &g_lexerf);
		if ((c = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
			ft_printf("21sh: %s: [%s]\n", ft_strshret(c), line,
					(g_shell->exitcode = 1));
		ft_astdel(&head);
		return (shell_end());
	}
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
				head = ft_lexer(line, &g_lexerf);
				if ((c = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
				{
					ft_printshret(c, line);
					if (c != SH_EXIT)
						g_shell->exitcode = 1;
				}
				check_bgend();
				ft_astdel(&head);
			}
			if (c != 3 && c != 4)
				addhistory(line);
		}
	}
	ft_makeraw(0);
	return (shell_end());
}
