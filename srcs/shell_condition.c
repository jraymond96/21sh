#include "shell.h"
#include "ft_str.h"

static int	ast_is(t_ast *ast, char *test)
{
	if (ast && ast->name && ft_strequ(ast->name, test))
		return (1);
	return (0);
}

static int	g_if_failed;
#include "ft_printf.h"
int	shell_else_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_ast	*al;
	int		efail;

	if (ft_strequ(ast->name, "not"))
	{
		if ((efail = ft_astiter(ast->right, res, iterf)))
			return (efail);
		*(int *)res = !*(int *)res;
		return (0);
	}
	if (!(al = ast->left) || !al->name
			|| (ft_strequ(al->name, "then") && !ast_is(al->left, "if") && !ast_is(al->left, "while")))
		return (SH_ELSEWCOND);
	if (!g_if_failed)
	{
		*(int *)res = *(int *)op[0];
		return (0);
	}
	g_if_failed = 0;
	return (ft_astiter(ast->right, res, iterf));
}

int	shell_cond_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	int		efail;
	int		i;

	(void)op;
	g_if_failed = 0;
	if (ft_strequ(ast->name, "if") || ft_strequ(ast->name, "while"))
		return (SH_CONDWTHEN);
	if (!ast_is(ast->left, "if") && !ast_is(ast->left, "while") && !ast_is(ast->parent, "else"))
		return (SH_THENWCOND);
	i = 0;
	while (1)
	{
		*(int *)res = 0;
		if ((efail = ft_astiter(ast->left->right, res, iterf)))
			return (efail);
		if (*(int *)res)
		{
			if (ast_is(ast->left, "if") || (ast_is(ast->left, "while") && !i))
				g_if_failed = 1;
			break ;
		}
		i = 1;
		if ((efail = ft_astiter(ast->right, res, iterf)))
			return (efail);
		if (!ast_is(ast->left, "while"))
			break ;
	}
	return (0);
}
