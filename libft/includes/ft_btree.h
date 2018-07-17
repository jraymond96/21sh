/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:43:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/06 02:16:59 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <stdlib.h>
# include "ft_list.h"

# ifndef FT_CMPFUNC_T
#  define FT_CMPFUNC_T

typedef int			(*t_cmpfunc)(const void *, const void *, size_t);

# endif

# ifndef FT_DELFUNC_T
#  define FT_DELFUNC_T

typedef void		(*t_delfunc)(void *, size_t);
typedef void		(*t_delfunc_d)(void *, size_t, void *);

void				content_delfunc(void *a, size_t b);

# endif

/*
** A binary tree node.
*/

typedef struct		s_btree
{
	void			*content;
	size_t			content_size;
	struct s_btree	*parent;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef void	(*t_btiter_d)(t_btree *, void *);

typedef struct		s_ptrpos
{
	size_t			start;
	size_t			len;
}					t_ptrpos;

/*
** Binary tree creations and deletions
** The btree_new function return a new node whose content is a duplicate of
** content.
** The btree_create function return a new node whose content is assigned to
** content.
*/

t_btree				*ft_btree_new(const void *content, size_t content_size);
t_btree				*ft_btree_create(void *content, size_t content_size);
void				ft_btree_delone(t_btree **abt, t_delfunc del);
void				ft_btree_del(t_btree **abt, t_delfunc del);

/*
** Binary tree insertions and removals.
** The insert functions insert the element and then return it.
** The erase functions extract the first occurence of 'content' then return
** it to be properly deleted by the user.
** Get functions work the same as search functions, except that they add the
** element if it is not found, so they dont allow occurences as insert
** functions do. The difference between getnew and getcreate functions is that
** they use the btree_new and btree_create function respectively to create a new
** node.
*/

t_btree				*ft_btree_insert(t_btree *bt, t_btree *elem);
t_btree				*ft_btree_insertf(t_btree *bt,
								t_btree *elem,
								t_cmpfunc cmp);
t_btree				*ft_btree_insertm(t_btree *bt,
								t_btree *elem,
								size_t pstart,
								size_t plen);

t_btree				*ft_btree_insert_p(t_btree **bt, t_btree *elem);
t_btree				*ft_btree_insertf_p(t_btree **bt,
								t_btree *elem,
								t_cmpfunc cmp);
t_btree				*ft_btree_insertm_p(t_btree **bt,
								t_btree *elem,
								size_t pstart,
								size_t plen);

t_btree				*ft_btree_erase(t_btree **bt,
								const void *content,
								size_t content_size);
t_btree				*ft_btree_erasef(t_btree **bt,
								const void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_erasem(t_btree **bt,
								const void *content,
								size_t pstart,
								size_t plen);

t_btree				*ft_btree_getnew(t_btree *bt,
								void *content,
								size_t content_size);
t_btree				*ft_btree_getnewf(t_btree *bt,
								void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_getnewm(t_btree *bt,
								void *content,
								size_t content_size,
								t_ptrpos ptrpos);
t_btree				*ft_btree_getcreate(t_btree *bt,
								void *content,
								size_t content_size);
t_btree				*ft_btree_getcreatef(t_btree *bt,
								void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_getcreatem(t_btree *bt,
								void *content,
								size_t content_size,
								t_ptrpos ptrpos);
t_ptrpos			make_ptrpos(size_t pstart, size_t plen);

/*
** Returns a binary tree storing all the removed nodes from the binary tree.
** This binary tree can then be freed or whatever the hell you want.
** The reason why these functions do not free the data is simple :
** We all hate leaks. Imagine the data stored (void *) is a structure that has
** an attribute that has been malloced before, if you just free the data
** (because you cant know the nature of a god damn void pointer) the attribute
** will be lost, unless the user keeps track of it, but you can't
** be sure of that.
*/

t_btree				*ft_btree_erase_all(t_btree **bt,
								const void *content,
								size_t content_size);
t_btree				*ft_btree_erasef_all(t_btree **bt,
								const void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_erasem_all(t_btree **bt,
								const void *content,
								size_t pstart,
								size_t plen);

/*
** Return the matched node that contain 'content'
*/

t_btree				*ft_btree_search(t_btree *bt,
								const void *content,
								size_t content_size);
t_btree				*ft_btree_searchf(t_btree *bt,
								const void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_searchm(t_btree *bt,
								const void *content,
								size_t pstart,
								size_t plen);

/*
** SPLAY searching : it simply put the matched node at root.
*/

t_btree				*ft_btree_splay(t_btree *bt,
								const void *content,
								size_t content_size);
t_btree				*ft_btree_splayf(t_btree *bt,
								const void *content,
								size_t content_size,
								t_cmpfunc cmp);
t_btree				*ft_btree_splaym(t_btree *bt,
								const void *content,
								size_t pstart,
								size_t plen);

/*
** Have you ever wondered how many times an element occurs on a binary
** tree ? Well this function has the answer !
*/

int					ft_btree_count(t_btree *bt,
								const void *content,
								size_t content_size);
int					ft_btree_countf(t_btree *bt,
								const void *content,
								size_t content_size,
								t_cmpfunc cmp);
int					ft_btree_countm(t_btree *bt,
								const void *content,
								size_t pstart,
								size_t plen);

/*
** Returns the position of the node relatively to another one. -1 means it
** is at his left, 1 at his right, and 0 means nowhere. The function checks the
** childs so if they points to the same node, it will gives you 0.
*/

int					ft_btree_pos(t_btree *bt, t_btree *elem);

/*
** Returns the root of the node wherever the node is on the binary tree.
*/

t_btree				*ft_btree_root(t_btree *bt);

/*
** Returns the left/right most child of the current node. If the binary tree's
** rules are respected, then the left most child is the minimum value and the
** right most child is the maximum value.
*/

t_btree				*ft_btree_left(t_btree *bt);
t_btree				*ft_btree_right(t_btree *bt);

/*
** Returns the equivalent in list of the given binary tree.
** And vice-versa, returns the equivalent in binary tree of the given list.
*/

t_list				*ft_btree_tolist(t_btree *bt);
t_list				*ft_btree_tolistv(t_btree *bt);
t_btree				*ft_btree_fromlist(t_list *lst);
t_btree				*ft_btree_fromlistf(t_list *lst, t_cmpfunc cmp);

t_btree				*ft_btree_copy(t_btree *bt);

/*
** Apply a function to each node of the binary tree by different modes.
*/

typedef enum	e_btmode
{
	BT_INORDER, BT_PREORDER, BT_POSTORDER, BT_LEVELORDER
}				t_btmode;

void				ft_btree_iter(t_btree *bt, void (*f)(t_btree *));
void				ft_btree_iterm(t_btree *bt,
								void (*f)(t_btree *),
								t_btmode mode);
void				ft_btree_iter_d(t_btree *bt, t_btiter_d f, void *data);
void				ft_btree_iterm_d(t_btree *bt,
								t_btiter_d f,
								t_btmode mode,
								void *data);

void				ft_btree_iterv(t_btree *bt, void (*f)(t_btree *));
void				ft_btree_itermv(t_btree *bt,
								void (*f)(t_btree *),
								t_btmode mode);
void				ft_btree_iterv_d(t_btree *bt, t_btiter_d f, void *data);
void				ft_btree_itermv_d(t_btree *bt,
								t_btiter_d f,
								t_btmode mode,
								void *data);

t_list				*ft_btree_tolistm(t_btree *bt, t_btmode mode);
t_list				*ft_btree_tolistmv(t_btree *bt, t_btmode mode);

/*
** Swap every attribute of the structure.
*/

void				ft_btree_swap(t_btree *a, t_btree *b, int childs);

/*
** Return the result of the left/right rotation of the binary tree.
** The rotateF and rotateM functions check if the binary tree can be rotated
** before rotating it. So if it can't be, the same binary tree is returned.
** Yes, there are cases where a binary tree cant be rotated, it happens when
** same values occurs on the right branch, left rotating it could break some
** fundamental rules of binary trees.
*/

t_btree				*ft_btree_leftrotate(t_btree *bt);
t_btree				*ft_btree_rightrotate(t_btree *bt);
t_btree				*ft_btree_leftrotatef(t_btree *bt, t_cmpfunc cmp);
t_btree				*ft_btree_rightrotatef(t_btree *bt, t_cmpfunc cmp);
t_btree				*ft_btree_leftrotatem(t_btree *bt,
										size_t start,
										size_t len);
t_btree				*ft_btree_rightrotatem(t_btree *bt,
										size_t start,
										size_t len);

/*
** AVL balancing : it simply perform rotations until both, left
** and right, branches have an equal height.
** Two calls are sufficient to have a perfectly balanced tree.
*/

t_btree				*ft_btree_balance(t_btree *bt);
t_btree				*ft_btree_balancef(t_btree *bt, t_cmpfunc cmp);
t_btree				*ft_btree_balancem(t_btree *bt, size_t start, size_t len);
void				balancem_childs(t_btree *bt, int *leftlen, int *rightlen,
								t_ptrpos ptrpos);

/*
** Returns the number of nodes.
** Returns the maximum depth.
** Print the binary tree.
*/

size_t				ft_btree_size(t_btree *bt);
size_t				ft_btree_depth(t_btree *bt);
void				ft_btree_dump(t_btree *bt);
void				ft_btree_dumpf(t_btree *bt, void (*f)(t_btree *));

/*
** Move a node and his childs, this function is used in SPLAY functions.
** Set the given node as an individual node.
*/

t_btree				*ft_btree_move(t_btree *bt, t_btree *elem);
t_btree				*ft_btree_disconnect(t_btree *bt);
t_btree				*ft_btree_connect(t_btree *a, t_btree *b, int lr);

#endif
