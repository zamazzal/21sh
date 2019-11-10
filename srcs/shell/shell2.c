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
	while(str[i] != '\0' && !ft_isspace(str[i]))
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
	while(i >= 0 && !ft_isspace(str[i]))
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

	x = ft_getlastpos(g_input, cursor.pos);
	if (x != -1)
	{
		cursor = ft_curleft(cursor, cursor.pos - x);
	}
	return (cursor);
}

t_cursor		ft_altu(t_cursor cursor)
{
	struct winsize ts;
	int prompt;
	int x;

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

int	ft_getlines()
{
	int i;
	struct winsize ts;
	t_cursor cursor;
	int prompt;
	int p;
	int f;

	i = 0;
	ts = ft_winsize();
	f = 1;
	prompt = ft_promptlen();
	cursor = ft_defaultcursor(&cursor);
	while (g_input[i] != '\0')
	{
		p = (cursor.y == 0) ? cursor.x + prompt : cursor.x;
		if (p >= ts.ws_col - 1 || g_input[cursor.pos - 1] == '\n')
		{
			f++;
			cursor.x = 0;
			cursor.y++;
		}
		else
			cursor.x++;
		cursor.pos++;
		i++;
	}
	return (f);
}

t_cursor		ft_altd(t_cursor cursor)
{
	struct winsize ts;
	int x;
	int len;
	int prompt;
	int p;

	ts = ft_winsize();
	len = ft_strlen(g_input);
	prompt = ft_promptlen();
	x = ft_getlines();
	if (cursor.y < x - 1)
	{
		cursor.pos += ft_getlinelen(cursor.y) - cursor.x;
		cursor.x = (cursor.y == 0) ? cursor.x + prompt : cursor.x;
		cursor.y++;
		p = ft_getlinelen(cursor.y);
		cursor.x = (cursor.x > p) ? p : cursor.x;
		cursor.pos += cursor.x + 1;
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

void	ft_cut(void)
{
	char *s1;
	char *s2;
	char *s;

	s1 = ft_strsub(g_input, 0, g_cpy.p1);
	s2 = ft_strsub(g_input, g_cpy.p2, ft_strlen(g_input));
	s = ft_strjoin(s1, s2);
	ft_strclr(g_input);
	ft_strdel(&s1);
	ft_strdel(&s2);
	g_input = ft_strcpy(g_input, s);
	ft_strdel(&s);
}

t_cursor	ft_checknoprint(int key, t_cursor cursor, char **history, int *i)
{
	int c;
	int f;

	if (key == ALTF)
	{
		if (g_cpy.p2 > g_cpy.p1)
		{
			g_cpy.p2--;
			cursor = ft_curleft(cursor, 1);
		}
		else
			ft_cpy();
	}
	if (key == ALTG)
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
		return (cursor);
	}
	if (key == ALTC)
	{
		if (g_cpy.buffer)
			ft_strdel(&g_cpy.buffer);
		g_cpy.buffer = ft_strsub(g_input, g_cpy.p1, g_cpy.p2 - g_cpy.p1);
		ft_cpy();
	}
	if (key == ALTV)
	{
		ft_cpy();
		if (g_cpy.buffer)
			cursor = ft_addstrtostr(g_cpy.buffer, cursor);
	}
	if (key == ALTX)
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
	if (key == RIGHT)
	{
		ft_cpy();
		if (cursor.pos < (int)ft_strlen(g_input))
		{
			cursor = ft_curright(cursor, 1);
		}
		return (cursor);
	}
	if (key == LEFT)
	{
		ft_cpy();
		if (cursor.pos - 1 >= 0)
		{
			cursor = ft_curleft(cursor, 1);
		}
		return (cursor);
	}
	if (key == BACKSPACE)
	{
		ft_cpy();
		if (cursor.pos > 0)
		{
			c = g_input[cursor.pos - 1];
			if (c == '\n')
			{
				f = cursor.pos;
				cursor = ft_curleft(cursor, 1);
				ft_strcpy(&g_input[f - 1], &g_input[f]);
			}
			else
			{
				ft_strcpy(&g_input[cursor.pos - 1], &g_input[cursor.pos]);
				cursor = ft_curleft(cursor, 1);
			}
		}
		return (cursor);
	}
	if (key == UP)
	{
		ft_cpy();
		if (*i >= 0)
		{
			ft_strcpy(g_input, history[*i]);
			cursor = ft_defaultcursor(&cursor);
			cursor = ft_curright(cursor, ft_strlen(g_input));
			if (*i > 0)
				(*i) = (*i) - 1;
		}
		return (cursor);
	}
	if (key == DOWN)
	{
		ft_cpy();
		if (history[*i + 1])
		{
			(*i) = (*i) + 1;
			ft_strcpy(g_input, history[*i]);
			cursor = ft_defaultcursor(&cursor);
			cursor = ft_curright(cursor, ft_strlen(g_input));
		}
		else
		{
			ft_strclr(g_input);
			cursor = ft_defaultcursor(&cursor);
		}
		return (cursor);
	}
	if (key == HOME)
	{
		ft_cpy();
		cursor = ft_defaultcursor(&cursor);
	}
	if (key == END)
	{
		ft_cpy();
		cursor = ft_defaultcursor(&cursor);
		cursor = ft_curright(cursor, ft_strlen(g_input));
	}
	if (key == ALTR)
	{
		ft_cpy();
		cursor = ft_altr(cursor);
	}
	if (key == ALTL)
	{
		ft_cpy();
		cursor = ft_altl(cursor);
	}
	if (key == ALTU)
	{
		ft_cpy();
		cursor = ft_altu(cursor);
	}
	if (key == ALTD)
	{
		ft_cpy();
		cursor = ft_altd(cursor);
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
