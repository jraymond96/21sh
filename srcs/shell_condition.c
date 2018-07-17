#include "shell.h"
#include "ft_str.h"

static int	left_if(t_ast *ast)
{
	if (!ast->left || !ast->left->name || !ft_strequ(ast->left->name, "if"))
		return (0);
	return (1);
}

static int	g_if_failed;

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
			|| (ft_strequ(al->name, "then") && !left_if(al)))
		return (SH_ELSEWIF);
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

	(void)op;
	g_if_failed = 0;
	if (ft_strequ(ast->name, "if"))
		return (SH_IFWTHEN);
	if (!left_if(ast))
	{
		if (!ast->parent || !ast->parent->name
				|| !ft_strequ(ast->parent->name, "else"))
			return (SH_THENWIF);
	}
	if ((efail = ft_astiter(ast->left->right, res, iterf)))
		return (efail);
	if (!*(int *)res)
		return (ft_astiter(ast->right, res, iterf));
	g_if_failed = 1;
	return (0);
}
