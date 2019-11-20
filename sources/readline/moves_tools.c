/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:04:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:07:41 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_innewline(t_getlines *line, t_cursor *cursor)
{
	(*line).f++;
	(*cursor).x = 0;
	(*cursor).y++;
}

int				ft_getlines(void)
{
	struct winsize	ts;
	t_cursor		cursor;
	int				prompt;
	t_getlines		line;

	line.i = 0;
	ts = ft_winsize();
	line.f = 1;
	prompt = ft_promptlen();
	cursor = ft_defaultcursor(&cursor);
	while (g_input[line.i] != '\0')
	{
		line.p = (cursor.y == 0) ? cursor.x + prompt : cursor.x;
		if (line.p >= ts.ws_col - 1 || g_input[cursor.pos - 1] == '\n')
			ft_innewline(&line, &cursor);
		else
			cursor.x++;
		cursor.pos++;
		line.i++;
	}
	return (line.f);
}

int				ft_firstinstr(char *str, int pos)
{
	int i;

	i = pos;
	while (i - 1 >= 0 && (ft_isprint(str[i - 1]) && !ft_isspace(str[i - 1])))
		i--;
	return (i);
}

int				ft_getlastpos(char *str, int pos)
{
	int i;

	i = pos;
	if (str[i] == '\0')
	{
		i--;
		if (i >= 0 && !ft_isspace(str[i]))
			return (ft_firstinstr(str, i));
	}
	while (i >= 0 && !ft_isspace(str[i]))
		i--;
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	if (i >= 0 && !ft_isspace(str[i]))
		return (ft_firstinstr(str, i));
	return (-1);
}
