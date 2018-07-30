#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

int	shell_arth_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	char		*ep;
	char		*epe;
	int			efail;
	t_exprdata	edata;
	EXPRT		val;

	(void)op;
	(void)iterf;
	ep = ast->name + 2;
	epe = ft_strend(ep);
	*epe = '\0';
	val = (EXPRT)0;
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((efail = ft_expr(ep, &val, &edata)))
	{
		*epe = ']';
		return (SH_EXPRERR + efail);
	}
	*epe = ']';
	if (!val)
		*(int *)res = 1;
	else
		*(int *)res = 0;
	return (0);
}

int	exp_cond(char *tld, int n[3], void *data, char **res)
{
	EXPRT		val;
	int			err;
	t_exprdata	edata;

	(void)data;
	val = (EXPRT)0;
	tld[n[0] - 1] = '\0';
	ft_bzero(&edata, sizeof(t_exprdata));
	edata.var_db = &g_shell->envp;
	if ((err = ft_expr(tld + 2, &val, &edata)))
	{
		tld[n[0] - 1] = ']';
		*res = NULL;
		return (SH_EXPRERR + err);
	}
	tld[n[0] - 1] = ']';
	*res = ft_lltoa(val);
	return (0);
	ft_printf("arithmetic expansion '%s' %d %d\n", tld + 3, n[1], n[2]);
}

int	exp_bslash(char *tld, int n[3], void *data, char **res)
{
	(void)n;
	(void)data;
//	if (*tld == '\033')
//		*res = ft_strdup("~");
//	else if (tld[1] == '~')
//		*res = ft_strdup("\033~");
//	else
		*res = ft_strndup(tld + 1, 1);
	return (0);
	ft_printf("bslash expansion %d '%s' %d %d\n", n[0], tld, n[1], n[2]);
}
