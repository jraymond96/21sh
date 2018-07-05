/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:39:12 by mmerabet          #+#    #+#             */
/*   Updated: 2018/05/28 16:08:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stdlib.h>

# ifndef FT_CMPFUNC_T
#  define FT_CMPFUNC_T

typedef int	(*t_cmpfunc)(const void *, const void *, size_t);

# endif

# ifndef FT_DELFUNC_T
#  define FT_DELFUNC_T

typedef void	(*t_delfunc)(void *, size_t);
typedef void	(*t_delfunc_d)(void *, size_t, void *);

void			content_delfunc(void *a, size_t b);

# endif

/*
** A linked list node.
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	struct s_list	*parent;
}					t_list;

t_list				*ft_strsplit_lst(const char *s, char sep);
t_list				*ft_strsplitstr_lst(const char *s, const char *sep);

/*
** Linked list creations and deletions
** The lstnew function return a new node whose content is a duplicate of content
** The lstcreate function retun a new node whose content is assigned to content
*/

t_list				*ft_lstnew(const void *content, size_t content_size);
t_list				*ft_lstcreate(void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, t_delfunc del);
void				ft_lstdelone_d(t_list **alst, t_delfunc_d del, void *data);
void				ft_lstdel(t_list **alst, t_delfunc del);
void				ft_lstdel_d(t_list **alst, t_delfunc_d del, void *data);
void				ft_lstdelv(t_list **alst, t_delfunc del);
void				ft_lstdelv_d(t_list **alst, t_delfunc_d del, void *data);

/*
** Linked list insertions and removals.
** The lstpush function insert the node at the end, and the lstpushfront
** function insert it at the front.
** The erase functions extract the first occurence of 'content' then return it
** to be properly deleted by the user.
*/

void				ft_lstadd(t_list **alst, t_list *elem);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstiter_d(t_list *lst,
							void (*f)(t_list *elem, void *data),
							void *data);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstmap_d(t_list *lst,
							t_list *(*f)(t_list *elem, void *data),
							void *data);
t_list				*ft_lstpush(t_list *lst, t_list *elem);
t_list				*ft_lstpush_p(t_list **lst, t_list *elem);
void				ft_lstpushfront(t_list **alst, t_list *elem);

t_list				*ft_lsterase(t_list **alst,
							const void *content,
							size_t content_size);
t_list				*ft_lsterasef(t_list **alst,
							const void *content,
							size_t content_size,
							t_cmpfunc cmp);
t_list				*ft_lsterasem(t_list **alst,
							const void *content,
							size_t pstart,
							size_t plen);

/*
** Return a linked list storing all removed nodes containing 'content' from the
** linked list. This list can then be freed or used.
** Their real role isn't really to erase the 'content' but to extract the nodes
** containing 'content'.
*/

t_list				*ft_lsterase_all(t_list **alst,
							const void *content,
							size_t content_size);
t_list				*ft_lsterasef_all(t_list **alst,
							const void *content,
							size_t content_size,
							t_cmpfunc cmp);
t_list				*ft_lsterasem_all(t_list **alst,
							const void *content,
							size_t pstart,
							size_t plen);

/*
** Return the node at a specific index.
** Return the matched node containing 'content'
*/

t_list				*ft_lstatpos(t_list *lst, int i);
t_list				*ft_lstfind(t_list *lst,
							const void *content,
							size_t content_size);
t_list				*ft_lstfindf(t_list *lst,
							const void *content,
							size_t content_size,
							t_cmpfunc cmp);
t_list				*ft_lstfindm(t_list *lst,
							const void *content,
							size_t pstart,
							size_t plen);

/*
** Count the occurences of 'content'.
*/

int					ft_lstcount(t_list *lst,
							const void *content,
							size_t content_size);
int					ft_lstcountf(t_list *lst,
							const void *content,
							size_t content_size,
							t_cmpfunc cmp);
int					ft_lstcountm(t_list *lst,
							const void *content,
							size_t pstart,
							size_t plen);

size_t				ft_lstsize(t_list *lst);
t_list				*ft_lstend(t_list *lst);
t_list				*ft_lstparent(t_list *lst);
t_list				*ft_lstcopy(t_list *lst);
t_list				*ft_lstcopyone(t_list *lst);
void				ft_lstswap(t_list *a, t_list *b);
t_list				*ft_lstsort(t_list *lst);
t_list				*ft_lstsortf(t_list *lst, t_cmpfunc cmp);
t_list				*ft_lstsortv(t_list *lst);
t_list				*ft_lstsortvf(t_list *lst, t_cmpfunc cmp);

#endif
