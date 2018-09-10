/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:27:44 by mmerabet          #+#    #+#             */
/*   Updated: 2018/07/08 17:41:07 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"
#include "ft_mem.h"

int				g_iread;

static int		ckmi(const char *str, t_mchi *mchi)
{
	int		i;
	int		pos;

	if (!mchi)
		return (0);
	if (mchi->type == 0 && ft_strnequ(str, mchi->str, ft_strlen(mchi->str)))
		return (1);
	else if (mchi->type == 2 && (pos = ft_strchrl_pos(mchi->str, '-')) == -1)
		return (ft_strchrln(mchi->str, *str) ? 1 : 0);
	else if (mchi->type == 2 && !(i = 0))
	{
		while (mchi->str[++pos])
		{
			i += (mchi->str[i] == '\\' ? 1 : 0);
			pos += (mchi->str[pos] == '\\' ? 1 : 0);
			if (*str >= mchi->str[i++] && *str <= mchi->str[pos])
				return (1);
		}
	}
	else if (mchi->type == 3 && checkwild3(&str, mchi, NULL, 0) == 1)
		return (1);
	return (0);
}

static int		checkwild1(const char **str, t_mchi *cur, t_mchi *nxt)
{
	int	i;

	i = 0;
	while (**str && (cur->t == 1 || (cur->t == 3 && i <= cur->len)
				|| !ckmi(*str, nxt)))
	{
		++i;
		++g_iread;
		++(*str);
		if ((cur->t < 3 && cur->len == 0) || (cur->t == 1 && i == cur->len)
				|| (cur->t == 2 && i == cur->len - 1))
			return (1);
	}
	if (cur->t == 3)
		return (i > cur->len ? 1 : -1);
	if (cur->t == 1 && i <= cur->len)
		return (-1);
	return (0);
}

static int		checkwild2(const char **str, t_mchi *cur, t_mchi *nxt)
{
	int	i;

	i = 0;
	while (**str && ckmi(*str, cur))
	{
		if (((cur->t == 2 || (cur->t == 3 && i > cur->len)) && ckmi(*str, nxt))
			|| ((cur->t < 3 && cur->len == 0) || (cur->t == 1 && i == cur->len)
				|| (cur->t == 2 && i == cur->len - 1)))
			return (1);
		++i;
		++g_iread;
		++(*str);
	}
	if (cur->t == 3)
		return (i > cur->len ? 1 : -1);
	if (cur->t == 1 && i < cur->len)
		return (-1);
	return (0);
}

static int		checktype(const char **str, t_mchi *cur, t_mchi *nxt)
{
	int	ret;

	if (cur->type == 1)
	{
		if ((!nxt && cur->len == -1) || (nxt && nxt->whatever))
			return (1);
		if ((ret = checkwild1(str, cur, nxt)) == 1)
			return (2);
		else if (ret == -1)
			return (0);
	}
	else if (cur->type == 2)
	{
		if (!ckmi((*str), cur))
			return (0);
		if ((ret = checkwild2(str, cur, nxt)) == 1)
			return (2);
		else if (ret == -1)
			return (0);
	}
	else if (cur->type == 3 && (ret = checkwild3(str, cur, nxt, 1)))
		return (ret == -1 ? 0 : 2);
	if (!*str && nxt && nxt->type == 1 && nxt->len == -1)
		return (1);
	return (2);
}

int				ft_strtks(const char *str, t_mchi *mchi, int option)
{
	int		len;

	g_iread = 0;
	while (mchi && *str)
	{
		if (mchi->type == 0)
		{
			len = ft_strlen(mchi->str);
			if (!ft_strnequ(str, mchi->str, len))
				return (0);
			str += len;
			g_iread += len;
		}
		else if ((len = checktype(&str, mchi, mchi->next)) != 2)
			return (len);
		mchi = mchi->next;
	}
	if (!*str && mchi && mchi->whatever)
		return (1);
	if (*str && !mchi && (option & RGX_END))
		return (1);
	return (*str || mchi ? 0 : 1);
}
