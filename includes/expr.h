/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 19:50:17 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/10 20:02:51 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPR_H
# define EXPR_H

# include "parser.h"

# define EXPR_DLM_VARV "*[aA_-zZ_@=1]*[aA0_-zZ9_]:*[aA_-zZ_@=1]"
# define EXPR_DLM_VAR "*[0-9]*[aA_-zZ_]:" EXPR_DLM_VARV
# define EXPR_DLM_EQU "*[+\\-*/%&|^@=1]=:="
# define INT_RGX "*[ ]*[0-9]:*[0-9]:*[ ]*[\\-+@=1]*[0-9]:*[\\-+@=1]*[0-9]"
# define EXPRT long

typedef struct		s_exprdata
{
	char			***var_db;
	char			**var_db2;
	t_args			*args;
	int				expr_lvl;
}					t_exprdata;

char				*ft_exprerr(int efail);
int					ft_expr(const char *expr,
						EXPRT *res,
						t_exprdata *data,
						t_args *args);

int					ft_ast_iter(t_ast *ast, t_exprdata *data);

int					expr_unary_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_incdec_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_arth_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_comp_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_cond_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_equ_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);
int					expr_tern_cb(t_ast *ast, void **op, void *res,
									t_iterf *iterf);

#endif
