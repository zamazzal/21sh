/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:59:39 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 18:48:37 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_cpy(void)
{
	if (g_cpy.p1 != -1 || g_cpy.p2 != -1)
	{
		g_cpy.p1 = -1;
		g_cpy.p2 = -1;
	}
}

void		ft_copy(void)
{
	if (g_input)
	{
		if (g_cpy.buffer)
			ft_strdel(&g_cpy.buffer);
		g_cpy.buffer = ft_strsub(g_input, g_cpy.p1, g_cpy.p2 - g_cpy.p1);
		ft_cpy();
	}
}

t_cursor	ft_paste(t_cursor cursor)
{
	ft_cpy();
	ft_clearbuffer();
	if (g_cpy.buffer)
		cursor = ft_addstrtostr(g_cpy.buffer, cursor);
	return (cursor);
}

static void	ft_cut(void)
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

t_cursor	ft_altx(t_cursor cursor)
{
	ft_clearbuffer();
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
