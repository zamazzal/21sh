/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_inline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:19:05 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:21:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor	ft_defaultcursor(t_cursor *cursor)
{
	(*cursor).pos = 0;
	(*cursor).x = 0;
	(*cursor).y = 0;
	return (*cursor);
}

t_cursor	ft_curright(t_cursor cur, int i)
{
	int				j;
	struct winsize	ts;
	int				prompt;
	int				p;

	j = 0;
	ts = ft_winsize();
	prompt = ft_promptlen();
	while (j < i)
	{
		cur.pos++;
		cur.x++;
		p = (cur.y == 0) ? cur.x + prompt : cur.x;
		if (p >= ts.ws_col || g_input[cur.pos - 1] == '\n')
		{
			cur.x = 0;
			cur.y++;
		}
		j++;
	}
	return (cur);
}

t_cursor	ft_curleft(t_cursor cur, int i)
{
	int				j;
	int				prompt;
	struct winsize	ts;

	j = 0;
	ts = ft_winsize();
	prompt = ft_promptlen();
	while (j < i)
	{
		if (cur.x < 0 && cur.y == 0)
			break ;
		cur.pos--;
		cur.x--;
		if (cur.x < 0 && cur.y > 0)
		{
			cur.y--;
			cur.x = ft_getlinelen(cur.y);
		}
		j++;
	}
	return (cur);
}
