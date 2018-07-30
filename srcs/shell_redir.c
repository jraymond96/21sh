#include "shell.h"
#include "ft_printf.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <fcntl.h>
#include <sys/wait.h>

int	shell_redir_cb(t_ast *ast, void **op, void *res, t_iterf *iterf)
{
	t_list	*redirs;
	t_redir	*r;
	t_list	*it;
	int		fd_o;
	int		save0, save1, save2;
	int		bits;

	redirs = list_redirections(&ast, (t_expf *)iterf->data);
	it = redirs;
	save0 = dup(0);
	save1 = dup(1);
	save2 = dup(2);
	char	closed_fd = 0;
	while (it)
	{
		r = (t_redir *)it->content;
		if (r->replace_fd)
		{
			if (r->fd_in == -1 && close(r->fd_out) != -1)
				closed_fd |= (1 << (r->fd_out - 1));
			else if (r->fd_in != -1)
			{
				if (closed_fd & (1 << (r->fd_in - 1)))
					close(r->fd_out);
				else
					dup2(r->fd_in, r->fd_out);
			}
		}
		else if (r->type == TK_LLEFT)
		{
			if (!r->names || !r->names->argv || !r->names->argv[0])
			{
				ft_printf_fd(2, "21sh: missing WORD for heredoc operator\n");
				break ;
			}
			char	*line;
			if ((fd_o = open("/tmp/.21sh-47965231.hdoc", O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
				ft_printf("fail write open\n");
			while (ft_printf("heredoc> ") && get_next_line(0, &line) >= 0)
			{
				if (ft_strequ(line, r->names->argv[0]) && ft_memdel((void **)&line))
					break ;
				ft_printf_fd(fd_o, "%s\n", line);
				ft_memdel((void **)&line);
			}
			close(fd_o);
			if ((fd_o = open("/tmp/.21sh-47965231.hdoc", O_RDONLY | O_CREAT, 0666)) == -1)
				ft_printf("fail read open\n");
			dup2(fd_o, r->fd_out);
			close(fd_o);
		}
		else
		{
			if (r->type == TK_LRIGHT)
				bits = (O_APPEND | O_WRONLY | O_CREAT);
			else if (r->type == TK_RIGHT)
				bits = (O_WRONLY | O_TRUNC | O_CREAT);
			else if (r->type == TK_LEFT)
				bits = (O_RDONLY);
			if ((fd_o = open(r->file, bits, 0666)) == -1)
			{
				ft_printf_fd(2, "21sh: could not open file: %s\n", r->names->argv[0]);
				break ;
			}
			else
			{
				dup2(fd_o, r->fd_out);
				close(fd_o);
			}
		}
		it = it->next;
	}
	ft_astiter(ast, res, iterf);
	dup2(save0, 0);
	close(save0);
	dup2(save1, 1);
	close(save1);
	dup2(save2, 2);
	close(save2);
	ft_lstdel(&redirs, content_delfunc);
	(void)op;
	return (0);
}
