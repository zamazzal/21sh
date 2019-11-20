/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:52:23 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:52:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_clearbuffer(void)
{
	ft_strdel(&g_search);
	ft_strdel(&g_autoc);
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

t_cursor	ft_addstrtostr(char *str2, t_cursor cursor)
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
