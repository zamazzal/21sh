/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:17:17 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/12 17:17:23 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor ft_right(t_cursor cursor)
{
    if (g_input)
    {
        ft_cpy();
        if (cursor.pos < (int)ft_strlen(g_input))
            cursor = ft_curright(cursor, 1);
    }
	return (cursor);
}

t_cursor ft_left(t_cursor cursor)
{
    if (g_input)
    {
        ft_cpy();
	    if (cursor.pos - 1 >= 0)
    		cursor = ft_curleft(cursor, 1);
    }
    return (cursor);
}

t_cursor ft_up(int *i, t_cursor cursor, char **history)
{
    char *tmp;

    ft_cpy();
	if (*i >= 0)
	{
        tmp = g_input;
		g_input = ft_strdup(history[*i]);
        ft_strdel(&tmp);
		cursor = ft_defaultcursor(&cursor);
	    cursor = ft_curright(cursor, ft_strlen(g_input));
		if (*i > 0)
			(*i) = (*i) - 1;
	}
	return (cursor);
}

t_cursor ft_down(int *i, t_cursor cursor, char **history)
{
    char *tmp;

    ft_cpy();
	if (history[*i + 1])
	{
		(*i) = (*i) + 1;
        tmp = g_input;
		g_input = ft_strdup(history[*i]);
        ft_strdel(&tmp);
		cursor = ft_defaultcursor(&cursor);
		cursor = ft_curright(cursor, ft_strlen(g_input));
	}
	else
	{
		ft_strdel(&g_input);
		cursor = ft_defaultcursor(&cursor);
	}
	return (cursor);
}