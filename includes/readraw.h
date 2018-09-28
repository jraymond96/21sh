/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readraw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:14:19 by mmerabet          #+#    #+#             */
/*   Updated: 2018/09/16 17:28:03 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READRAW_H
# define READRAW_H

# include "ft_list.h"

typedef struct		s_bufferl
{
	char			*line;
	char			*save;
	size_t			size;
	int				len;
	size_t			cursor;
	int				x;
	int				y;
	int				ys;
	int				xs;
	int				w;
	int				h;
	int				ni;
	int				sm;
	int				sm_x;
	int				sm_y;
	size_t			sm_cursor;
	t_list			*it;
}					t_bufferl;

typedef struct		s_selectmode
{
	int				save_x;
	int				save_y;
	int				save_cur;
}					t_slctmode;

void				reprint_line3(t_bufferl *bl, t_slctmode *sm);
void				handle_xy_cursor(t_bufferl *bl, int left);
int					selectmode(t_bufferl *bl, int c);
void				add_char(t_bufferl *bl, int c);
void				delete_char(t_bufferl *bl);
void				escape_char(t_bufferl *bl, int c);
void				move_history(t_bufferl *bl, int c);
void				reprint_sm(t_bufferl *bl);
void				move_word(t_bufferl *bl, int c);
void				move_end(t_bufferl *bl, int c);
int					ft_readraw(char *line, size_t size);

#endif
