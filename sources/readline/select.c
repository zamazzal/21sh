/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:50:53 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:51:20 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor	ft_altright(t_cursor cursor)
{
	if (g_input)
	{
		if (cursor.pos < (int)ft_strlen(g_input))
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

t_cursor	ft_altleft(t_cursor cursor)
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
