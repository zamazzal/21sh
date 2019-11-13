/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:39:00 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/12 17:39:08 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor ft_home(t_cursor cursor)
{
    if (g_input)
    {
        ft_cpy();
	    cursor = ft_defaultcursor(&cursor);
        
    }
    return (cursor);
}

t_cursor ft_end(t_cursor cursor)
{
    if (g_input)
    {
        ft_cpy();
        cursor = ft_defaultcursor(&cursor);
        cursor = ft_curright(cursor, ft_strlen(g_input));
    }
    return (cursor);
}

t_cursor ft_backspace(t_cursor cursor)
{
    int c;
    int f;

    if (g_input)
    {
        ft_cpy();
		if (cursor.pos > 0)
		{
			c = g_input[cursor.pos - 1];
			if (c == '\n')
			{
				f = cursor.pos;
				cursor = ft_curleft(cursor, 1);
				ft_strcpy(&g_input[f - 1], &g_input[f]);
			}
			else
			{
				ft_strcpy(&g_input[cursor.pos - 1], &g_input[cursor.pos]);
				cursor = ft_curleft(cursor, 1);
			}
		}
        if (*g_input == '\0')
            ft_strdel(&g_input);
    }
    return (cursor);
}