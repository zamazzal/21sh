/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:01:37 by zamazzal          #+#    #+#             */
/*   Updated: 2019/08/06 15:22:40 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

t_cursor	ft_checknoprint(int key, t_cursor cursor, char **history, int *i)
{
	if (key == RIGHT)
	{
		if (cursor.pos < (int)ft_strlen(g_input))
		{
			cursor = ft_curright(cursor, 1);
			cursor.pos++;
		}
		return (cursor);
	}
	if (key == LEFT)
	{
		if (cursor.pos - 1 >= 0)
		{
			cursor = ft_curleft(cursor, 1);
			cursor.pos--;
		}
		return (cursor);
	}
	if (key == BACKSPACE)
	{
		if (cursor.pos >= 0)
		{
			ft_strcpy(&g_input[cursor.pos - 1], &g_input[cursor.pos]);
			cursor.pos = (cursor.pos - 1 >= 0) ? (cursor.pos - 1) : 0;
			cursor = ft_curleft(cursor, 1);
		}
		return (cursor);
	}
	if (key == UP)
	{
		if (*i >= 0)
		{
			ft_strcpy(g_input, history[*i]);
			cursor = ft_defaultcursor(&cursor);
			cursor.pos = ft_strlen(g_input);
			cursor = ft_curright(cursor, cursor.pos);
			if (*i > 0)
				(*i) = (*i) - 1;
		}
	}
	if (key == DOWN)
	{
		if (history[*i + 1])
		{
			(*i) = (*i) + 1;
			ft_strcpy(g_input, history[*i]);
			cursor = ft_defaultcursor(&cursor);
			cursor.pos = ft_strlen(g_input);
			cursor = ft_curright(cursor, cursor.pos);
		}
		else
		{
			ft_strclr(g_input);
			cursor = ft_defaultcursor(&cursor);
		}
	}
	if (key == HOME)
	{
		cursor = ft_defaultcursor(&cursor);
	}
	if (key == END)
	{
		cursor = ft_defaultcursor(&cursor);
		cursor.pos = ft_strlen(g_input);
		cursor = ft_curright(cursor, cursor.pos);
	}
	return (cursor);
}

char	*ft_prepareinput(void)
{
	char			*input;

	SAFE(input = ft_strnew(BUFFER_SIZE));
	ft_strclr(input);
	return (input);
}

void	ft_endinput(char **cmds, char *input)
{
	ft_freetable(&cmds);
	ft_strdel(&input);
}
