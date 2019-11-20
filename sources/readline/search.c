/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:56:17 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:57:01 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor	ft_ctrlr(t_cursor cursor, char **history)
{
	static int i = 0;

	if (!g_input && !g_search)
		return (cursor);
	if (!g_search)
		g_search = ft_strdup(g_input);
	ft_cpy();
	while (history[i])
	{
		if (ft_strstr(history[i], g_search))
		{
			ft_strdel(&g_input);
			g_input = ft_strdup(history[i]);
			cursor = ft_defaultcursor(&cursor);
			cursor = ft_curright(cursor, ft_strlen(g_input));
			i++;
			return (cursor);
		}
		i++;
	}
	if (!history[i])
		i = 0;
	return (cursor);
}
