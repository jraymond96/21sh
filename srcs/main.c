/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 20:01:03 by jraymond         ###   ########.fr       */
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

#include "../logger/incs/logger.h"

static t_op			g_ops[] = {
	{"\\:=", OP_BINARY | OP_ASSOCRL},
	{DLM_REDP, OP_BINARY},
	{"not:!", OP_UNARYL},
	{"|", OP_BINARY},
	{"&", OP_BINARY | OP_ASSOCRL},
	{"&&:||", OP_BINARY},
	{",", OP_BINARY | OP_ASSOCRL},
	{"if:while", OP_UNARYL},
	{"then", OP_BINARY | OP_ASSOCRL},
	{"else", OP_BINARY},
	{";:\n", OP_BINARY | OP_ASSOCRL}
};

static t_exp		g_exps[] = {
	{"\\\\*[@=1]", exp_var},
	{"$*[aA0_-zZ9_]:$?", exp_var},
	{"$*[0-9]:$@", exp_arg},
	{"*[$(?);(?);`?`;${?};\"*\";'*'@b]", exp_cmd},
	{"*[$((?));(?);\"*\";'*'@b]", exp_arth},
	{"~", exp_tild},
	{"*[${?};\"*\";'*'@b]", exp_dvar},
	{"*[\"*\"@b]:'*':$'*'", exp_farg},
	{"*[\"'@=1]*[@>0]:$'*[@>0]:\":':$'", exp_farg},
	{"*[`?`;$(?);${?};\"*\";'*'@b]", exp_cmd},
	{"*[$\\[*\\];\"*\";'*'@b]", exp_cond},

	{EXP_BRACES, NULL},
	{EXP_SUBSHELL, NULL}
};

static t_expf		g_expf = {
	g_exps, sizeof(g_exps), NULL, 0
};

static t_lexerf		g_lexerf = {
	{
		DLM_WORD, DLM_STOP, DLM_LSTOP, DLM_RSTOP, DLM_HSTOP,
		g_exps, sizeof(g_exps) / sizeof(t_exp), NULL, NULL, NULL
	}, g_ops, sizeof(g_ops) / sizeof(t_op), TK_CMD, TK_OP, NULL
};

static t_astfunc	g_shell_callbacks[] = {
	{EXP_BRACES, shell_lists_cb, NULL, 3},
	{EXP_SUBSHELL, shell_lists_cb, NULL, 3},
	{"*[$\\[*\\];\"*\";'*'@b]", shell_arth_cb, NULL, 3},
	{"", shell_cmd_cb, NULL, 3},
	{"if:then", NULL, shell_cond_cb, 0},
	{"else:not:!", shell_else_cb, shell_else_cb, -1},
	{"&&:||", shell_andor_seco_cb, NULL, -1},
	{"&", NULL, shell_bckgrnd_cb, 0},
	{",:;:\n", NULL, shell_andor_seco_cb, 0},
	{"|", NULL, shell_pipe_cb, 0},
	{"\\:=", NULL, shell_equal_cb, 0},
	{DLM_REDP, NULL, shell_redir_cb, 0},
};

// Structure definissant les pointeurs sur fonctions a appeles a quel moment,
// les fonctions sont dans le fichiers shell_callbacks.c
static t_iterf		g_shell_iterf = {
	// Les fonctions qui seront appeles
	g_shell_callbacks, sizeof(g_shell_callbacks) / sizeof(t_astfunc),
	(void *)&g_expf, 0, sizeof(int)
};

static t_allf		g_allf = {
	&g_lexerf.parserf, &g_lexerf, &g_shell_iterf, &g_expf
};

void	printprompt(int i)
{
	static int	e = 50;
	static int	rev = 0;
	char		*start_pwd;
	char		*prompt;
	char		*nprompt;

	if (i)
	{
		ft_getcursor(&i, NULL);
		if (i > 1)
			ft_printf("%{0}%{invert}%%%{0}\n");
	}
	if ((prompt = ft_getenv("PROMPT", g_shell->envp)))
	{
		nprompt = NULL;
		ft_strexpand(prompt, &nprompt, 0, g_shell->allf->expf);
		ft_printf(nprompt);
		free(nprompt);
		return ;
	}
	start_pwd = NULL;
	if (ft_strstr_pos(g_shell->pwd, g_shell->homepwd) == 0)
		start_pwd = g_shell->pwd + ft_strlen(g_shell->homepwd);
	ft_printf("%{0}%{bold}%C%{0} %{lred}%s %{lcyan}%s%s%{0} ",
			L'㋜', (g_shell->user ? g_shell->user : "21sh"), (start_pwd ? "~" : ""),
			(start_pwd ? start_pwd : g_shell->pwd));
	if (g_shell->exitcode)
		ft_printf("%{bold/lred}(%d)%C%{0} ", g_shell->exitcode, L'❯');
	else
		ft_printf("%{;%1$d;%1$d;%1$d}%{bold}%C%{0} ", (e += (rev ? -10 : 10)),
			L'❯');
	if (rev && e <= 50)
		rev = 0;
	if (!rev && e >= 250)
		rev = 1;
}

int			main(int argc, char **argv, char **envp)
{
	char	line[8192];
	t_ast	*head;
	int		c;
	int		ret;
	char	*name;
	
	if (logger_init(D_TRACE, "/tmp/out.log") != 0)
		printf("failed to open the logger\n");
	name = argv[0];
	if ((name = ft_strrchr(argv[0], '/')))
		++name;
	shell_begin(name, argc, argv, envp);
	if (g_shell->bits & (1 << 0))
	{
		g_lexerf.parserf.def_word = DLM_WORD_N;
		g_lexerf.parserf.def_hstop = DLM_HSTOP_N;
	}
	g_expf.data = &g_allf;
	g_lexerf.data = &g_allf;
	g_lexerf.parserf.data = &g_allf;
	g_shell_iterf.data = &g_allf;
	g_expf.data = &g_allf;
	g_shell->allf = &g_allf;
	if (g_shell->script)
	{
		++g_shell->curargs->argv;
		--g_shell->curargs->argc;
		head = ft_lexer(g_shell->script, &g_lexerf);
		if ((c = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
		{
			ft_astdel(&head);
			if (c == SH_EXIT)
				return (shell_end());
			ft_printf_fd(2, "%s: %s: [%s]\n", g_shell->name, ft_strshret(c), g_shell->script,
					(g_shell->exitcode = 1));
		}
		ft_astdel(&head);
		--g_shell->curargs->argv;
		++g_shell->curargs->argc;
		return (shell_end());
	}
	if (g_shell->start_cmd)
	{
		head = ft_lexer(g_shell->start_cmd, &g_lexerf);
		if ((c = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
		{
			ft_astdel(&head);
			if (c == SH_EXIT)
				return (shell_end());
			ft_printf_fd(2, "%s: %s: [%s]\n", g_shell->name, ft_strshret(c), g_shell->script,
					(g_shell->exitcode = 1));
		}
		ft_astdel(&head);
	}
	ft_bzero(line, 8192);
	c = 0;
	while (g_shell->running)
	{
		printprompt(1);
		g_shell->kill_builtin = 0;
		if ((c = ft_readraw3(ft_strclr(line), 8192)))
		{
			ft_putchar('\n');
			if (c == 4 && !(g_shell->running = 0))
				ft_strcpy(ft_strclr(line), "exit");
			if (c != 3)
			{
				if (!line[0] && c == 13 && !(g_shell->exitcode = 0))
				{
					check_bgend();
					continue ;
				}
				head = ft_lexer(line, &g_lexerf);
			//	ft_astprint(head, 0);
				if ((ret = ft_astiter(head, &g_shell->exitcode, &g_shell_iterf)))
				{
					ft_printshret(ret, line);
					if (ret != SH_EXIT)
						g_shell->exitcode = 1;
				}
				check_bgend();
				ft_astdel(&head);
			}
			else
				g_shell->exitcode = 1;
			if (c != 3 && c != 4)
				addhistory(line);
		}
	}
	ft_makeraw(0);
	logger_close();
	return (shell_end());
}
