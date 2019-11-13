/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:59:39 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/12 19:00:44 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor    ft_altright(t_cursor cursor)
{
    if (g_input)
    {
        if (cursor.pos + 1 < (int)ft_strlen(g_input))
        {
            if (g_cpy.p1 == -1)
                g_cpy.p1 = g_cursor.pos;
            if (g_cpy.p2 == -1)
                g_cpy.p2 = 1 + g_cursor.pos;
            else
                g_cpy.p2++;
                cursor = ft_curright(cursor, 1);
        }
    }
	return (cursor);
}

t_cursor    ft_altleft(t_cursor cursor)
{
    if (g_input)
    {
        if (g_cpy.p2 > g_cpy.p1)
        {
            g_cpy.p2--;
            cursor = ft_curleft(cursor, 1);
        }
        else
            ft_cpy();
    }
    return (cursor);
}

void    ft_copy(void)
{
    if (g_input)
    {
        if (g_cpy.buffer)
            ft_strdel(&g_cpy.buffer);
        g_cpy.buffer = ft_strsub(g_input, g_cpy.p1, g_cpy.p2 - g_cpy.p1);
        ft_cpy();
    }
}

t_cursor	ft_straddchrinpos(char c, t_cursor cursor)
{
	char *tmp;

	ft_cpy();
	tmp = ft_strsub(g_input, 0, cursor.pos);
    tmp = ft_straddchr(tmp, c);
    tmp = ft_strjoin_lite(tmp, &g_input[cursor.pos]);
    ft_strdel(&g_input);
    g_input = tmp;
	cursor = ft_curright(cursor, 1);
	return (cursor);
}

t_cursor		ft_addstrtostr(char *str2, t_cursor cursor)
{
	int i;

	i = 0;
	while (str2[i])
	{
		cursor = ft_straddchrinpos(str2[i], cursor);
		i++;
	}
	return (cursor);
}

t_cursor    ft_paste(t_cursor cursor)
{
    ft_cpy();
	if (g_cpy.buffer)
		cursor = ft_addstrtostr(g_cpy.buffer, cursor);
    return (cursor);
}

void	ft_cut(void)
{
	char *s1;
	char *s2;

	s1 = ft_strsub(g_input, 0, g_cpy.p1);
	s2 = ft_strsub(g_input, g_cpy.p2, ft_strlen(g_input));
    ft_strdel(&g_input);
	g_input = ft_strjoin(s1, s2);
    ft_strdel(&s1);
    ft_strdel(&s2);
}

t_cursor    ft_altx(t_cursor cursor)
{
    if (g_input)
    {
        if (g_cpy.p2 > g_cpy.p1)
        {
            if (g_cpy.buffer)
                ft_strdel(&g_cpy.buffer);
            g_cpy.buffer = ft_strsub(g_input, g_cpy.p1, g_cpy.p2 - g_cpy.p1);
            ft_cut();
            cursor = ft_curleft(cursor, g_cpy.p2 - g_cpy.p1);
        }
        ft_cpy();
    }
    return (cursor);
}