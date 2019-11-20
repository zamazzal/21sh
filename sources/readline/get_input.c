/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:20:52 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:21:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_checkkey(int i)
{
	if (i == DOWN || i == RIGHT || i == LEFT || i == UP)
		return (i);
	if (i == ENTRE || i == ESC || i == BACKSPACE || i == CTRLD)
		return (i);
	if (i == HOME || i == END)
		return (i);
	if (i == ALTR || i == ALTL || i == ALTU || i == ALTD)
		return (i);
	if (i == ALTC || i == ALTV || i == ALTX || i == ALTF)
		return (i);
	if (i == ALTG || i == ALTA)
		return (i);
	if (i == TAP || i == CTRLR)
		return (i);
	return (0);
}

int		ft_readx(void)
{
	char	*buff;
	int		key;
	int		r;

	buff = ft_strnew(BUFFER_SIZE);
	r = read(0, buff, BUFFER_SIZE);
	buff[r] = '\0';
	key = (*(int*)buff);
	if (ft_checkkey(key))
	{
		ft_strdel(&buff);
		return (key);
	}
	else
	{
		ft_clearbuffer();
		if (g_input)
			ft_addstrtostr(buff, g_cursor);
		else
			g_input = ft_strdup(buff);
		g_cursor = ft_curright(g_cursor, r);
	}
	ft_strdel(&buff);
	return (0);
}
