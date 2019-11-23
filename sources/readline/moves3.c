/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:02:31 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:03:53 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor		ft_altr(t_cursor cursor)
{
	int x;

	ft_cpy();
	if (g_input)
	{
		x = ft_getnextpos(g_input, cursor.pos);
		if (x != -1)
		{
			cursor = ft_curright(cursor, x - cursor.pos);
		}
	}
	return (cursor);
}

t_cursor		ft_altl(t_cursor cursor)
{
	int x;

	ft_cpy();
	if (g_input)
	{
		x = ft_getlastpos(g_input, cursor.pos);
		if (x != -1)
		{
			cursor = ft_curleft(cursor, cursor.pos - x);
		}
	}
	return (cursor);
}

t_cursor		ft_altu(t_cursor cursor)
{
	struct winsize	ts;
	int				prompt;
	int				x;

	ft_cpy();
	if (!g_input)
		return (cursor);
	ts = ft_winsize();
	prompt = ft_promptlen();
	if (cursor.y > 0)
	{
		cursor.y--;
		x = ft_getlinelen(cursor.y);
		cursor.pos -= cursor.x;
		cursor.x = (cursor.y == 0) ? cursor.x - prompt : cursor.x;
		cursor.x = (cursor.x > x) ? x : cursor.x;
		cursor.x = (cursor.x < 0) ? 0 : cursor.x;
		cursor.pos -= x - cursor.x + 1;
		if (cursor.pos < 0)
			cursor.pos = 0;
	}
	return (cursor);
}

t_cursor		ft_altd(t_cursor cursor)
{
	struct winsize	ts;
	int				x;
	int				len;
	int				prompt;
	int				p;

	if (!g_input)
		return (cursor);
	ts = ft_winsize();
	len = ft_strlen(g_input);
	prompt = ft_promptlen();
	x = ft_getlines();
	ft_cpy();
	if (cursor.y < x - 1)
	{
		ft_calcpos(&cursor, prompt, &p);
		if (cursor.pos > len)
		{
			cursor.pos = len;
			cursor.x = ft_getlinelen(cursor.y) - cursor.y;
			if (ft_strchr(g_input, '\n'))
				cursor.x++;
		}
	}
	return (cursor);
}
