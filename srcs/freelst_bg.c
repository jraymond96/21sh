#include "shell.h"
#include "ft_mem.h"

void		del(void *content, size_t size)
{
	(void)size;
	ft_delenv(&((t_inffork *)content)->cmd);
	ft_memdel(&content);
}

void		freelst_bg(void)
{
	t_list	*elem;
	t_list	*next;

	if (!(elem = g_shell->bgproc))
		return ;
	while (elem)
	{
		next = elem->next;
		ft_lstdelone(&elem, del);
		elem = next;
	}
}
