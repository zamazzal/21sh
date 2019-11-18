/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 14:01:37 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 17:20:50 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int			ft_firstinstr(char *str, int pos)
{
	int i;

	i = pos;
	while (i - 1 >= 0 && (ft_isprint(str[i - 1]) && !ft_isspace(str[i - 1])))
		i--;
	return (i);
}

int			ft_getnextpos(char *str, int pos)
{
	int i;

	i = pos;
	while (str[i] != '\0' && !ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] != '\0' && !ft_isspace(str[i]))
		return (i);
	return (-1);
}

int			ft_getlastpos(char *str, int pos)
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

t_cursor		ft_altr(t_cursor cursor)
{
	int x;

	ft_cpy();
	x = ft_getnextpos(g_input, cursor.pos);
	if (x != -1)
	{
		cursor = ft_curright(cursor, x - cursor.pos);
	}
	return (cursor);
}

t_cursor		ft_altl(t_cursor cursor)
{
	int x;

	ft_cpy();
	x = ft_getlastpos(g_input, cursor.pos);
	if (x != -1)
	{
		cursor = ft_curleft(cursor, cursor.pos - x);
	}
	return (cursor);
}

t_cursor		ft_altu(t_cursor cursor)
{
	struct winsize	ts;
	int				prompt;
	int				x;

	ft_cpy();
	ts = ft_winsize();
	prompt = ft_promptlen();
	if (cursor.y > 0)
	{
		cursor.y--;
		x = ft_getlinelen(cursor.y);
		cursor.pos -= cursor.x;
		cursor.x = (cursor.y == 0) ? cursor.x - prompt : cursor.x;
		cursor.x = (cursor.x > x) ? x : cursor.x;
		cursor.x = (cursor.x < 0) ? 0 : cursor.x;
		cursor.pos -= x - cursor.x + 1;
		if (cursor.pos < 0)
			cursor.pos = 0;
	}
	return (cursor);
}

void	ft_innewline(t_getlines *line, t_cursor *cursor)
{
	(*line).f++;
	(*cursor).x = 0;
	(*cursor).y++;
}

int	ft_getlines(void)
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

void			ft_calcpos(t_cursor *cursor, int prompt, int *p)
{
	(*cursor).pos += ft_getlinelen((*cursor).y) - (*cursor).x;
	(*cursor).x = ((*cursor).y == 0) ? (*cursor).x + prompt : (*cursor).x;
	(*cursor).y++;
	*p = ft_getlinelen((*cursor).y);
	(*cursor).x = ((*cursor).x > *p) ? *p : (*cursor).x;
	(*cursor).pos += (*cursor).x + 1;
}

t_cursor		ft_altd(t_cursor cursor)
{
	struct winsize	ts;
	int				x;
	int				len;
	int				prompt;
	int				p;

	ts = ft_winsize();
	len = ft_strlen(g_input);
	prompt = ft_promptlen();
	x = ft_getlines();
	ft_cpy();
	if (cursor.y < x - 1)
	{
		ft_calcpos(&cursor, prompt, &p);
		if (cursor.pos > len)
		{
			cursor.pos = len;
			cursor.x = ft_getlinelen(cursor.y) - cursor.y;
			if (ft_strchr(g_input, '\n'))
				cursor.x++;
		}
	}
	return (cursor);
}

t_cursor	ft_autocompletion(t_cursor cursor, char **history)
{
	static int i = 0;

	if (!g_input)
		return (cursor);
	while (history[i])
	{
		if (ft_strnstr(history[i], g_input, ft_strlen(g_input)))
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

t_cursor	ft_checknoprint(int key, t_cursor cursor, char **history, int *i)
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
	if (key == TAP)
		cursor = ft_autocompletion(cursor, history);
	cursor = moves(cursor, key);
	return (cursor);
}

void	ft_endinput(char **cmds, char *input)
{
	ft_freetable(&cmds);
	ft_strdel(&input);
}
