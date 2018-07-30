#include <stddef.h>

typedef struct		s_iterf t_iterf;

typedef int			(*t_astfunc_cb)(t_ast *, void **, void *, t_iterf *);

typedef struct		s_astfunc
{
	char			*name;
	t_astfunc_cb	func;
	t_astfunc_cb	unary_func;
	int				post;
}					t_astfunc;

struct				s_iterf
{
	t_astfunc_cb	op_func;
	t_astfunc		*funcs;
	size_t			funcs_len;
	int				resolve_first;
	int				opmissing_err;
};
