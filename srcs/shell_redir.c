#include "shell.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <sys/wait.h>

int	shell_redir_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_list	*redirs;
	t_redir	*r;
	t_list	*it;
	pid_t	pid;
	int		fd_o;
	int		bits;

	redirs = list_redirections(&ast);
	while (ast->left)
		ast = ast->left;
	it = redirs;
	if (!(pid = fork()))
	{
		char	closed_fd = 0;
		while (it)
		{
			r = (t_redir *)it->content;
			if (r->replace_fd)
			{
				if (r->fd_in == -1)
				{
					closed_fd |= (1 << (r->fd_out - 1));
					close(r->fd_out);
				}
				else
				{
					if (closed_fd & (1 << (r->fd_in - 1)))
						close(r->fd_out);
					else
						dup2(r->fd_in, r->fd_out);
				}
			}
			else
			{
				if (r->type == TK_LRIGHT)
					bits = (O_APPEND | O_WRONLY | O_CREAT);
				else if (r->type == TK_RIGHT)
					bits = (O_WRONLY | O_CREAT);
				else if (r->type == TK_LEFT)
					bits = (O_RDONLY);
				fd_o = open(r->names->argv[0], bits, 0666);
				dup2(fd_o, r->fd_out);
				close(fd_o);
			}
			it = it->next;
		}
		ft_astiter(ast, res, iterf);
		exit(*(int *)res);
	}
	else
	{
		wait((int *)res);
		*(int *)res >>= 8;
	}
	ft_lstdel(&redirs, content_delfunc);
	(void)op;
	(void)iterf;
	return (0);
}
