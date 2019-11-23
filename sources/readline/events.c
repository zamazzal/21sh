/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:53:55 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 15:59:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static t_cursor	moves(t_cursor cursor, int key)
{
	if (key == RIGHT)
		cursor = ft_right(cursor);
	if (key == LEFT)
		cursor = ft_left(cursor);
	if (key == HOME)
		cursor = ft_home(cursor);
	if (key == END)
		cursor = ft_end(cursor);
	if (key == ALTR)
		cursor = ft_altr(cursor);
	if (key == ALTL)
		cursor = ft_altl(cursor);
	if (key == ALTU)
		cursor = ft_altu(cursor);
	if (key == ALTD)
		cursor = ft_altd(cursor);
	return (cursor);
}

t_cursor		ft_checknoprint(int key, t_cursor cursor,
char **history, int *i)
{
	if (key == ALTF)
		cursor = ft_altleft(cursor);
	if (key == ALTG)
		cursor = ft_altright(cursor);
	if (key == ALTC)
		ft_copy();
	if (key == ALTV)
		cursor = ft_paste(cursor);
	if (key == ALTX)
		cursor = ft_altx(cursor);
	if (key == BACKSPACE)
		cursor = ft_backspace(cursor);
	if (key == UP)
		cursor = ft_up(i, cursor, history);
	if (key == DOWN)
		cursor = ft_down(i, cursor, history);
	if (key == CTRLR)
		cursor = ft_ctrlr(cursor, history);
	if (key == TAP)
		cursor = ft_autocompletion(cursor);
	cursor = moves(cursor, key);
	return (cursor);
}
