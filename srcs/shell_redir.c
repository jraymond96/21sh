#include "shell.h"
#include "ft_printf.h"

int	shell_redir_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_list	*redirs;
	t_list	*it;

	ft_printf("REDIR CALLBACK: '%s'\n", ast->name);
	redirs = list_redirections(&ast);
//	shell_cmd_cb(ast, op, res, iterf);
	ft_printf("Command: '%s'\n", ast->name);
	it = redirs;
	while (it)
	{
		t_rdrctn *r = (t_rdrctn *)it->content;
		ft_printf("\tredirection: type:%s full:'%s' out:%d in:%d file:'%s'\n",
					typestr(r->type), r->str, r->fd_out, r->fd_in, 
					(r->names && r->names->argv[0] ? r->names->argv[0] : NULL));
		it = it->next;
	}
	ft_lstdel(&redirs, content_delfunc);
	(void)op;
	(void)res;
	(void)iterf;
	return (0);
}
