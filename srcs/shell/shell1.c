/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:48:31 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/15 17:56:47 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_checkkey(int i)
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
	if (i == TAP)
		return (i);
	return (0);
}

int			ft_readx()
{
	char *buff;
	int key;
	int r;

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
		if (g_input)
			ft_addstrtostr(buff, g_cursor);
		else
			g_input = ft_strdup(buff);
		g_cursor = ft_curright(g_cursor, r);
	}
	ft_strdel(&buff);
	return (0);
}

t_cursor	ft_defaultcursor(t_cursor *cursor)
{
	(*cursor).pos = 0;
	(*cursor).x = 0;
	(*cursor).y = 0;
	return (*cursor);
}

struct winsize	ft_winsize(void)
{
	struct winsize ts;

    ioctl(0, TIOCGWINSZ, &ts);
	return (ts);
}

void	ft_selected(int i)
{
	if (i == g_cpy.p1)
	{
		ft_putterm("mr");
		ft_putterm("us");
	}
	if (i == g_cpy.p2)
	{
		ft_putterm("me");
		ft_putterm("ue");
	}
}

int		ft_showstr(char *str)
{
	int i;
	int x;
	struct winsize ts;
	int p;
	int y;

	i = 0;
	x = ft_promptlen();
	ts = ft_winsize();
	p = 0;
	while (str[i] != '\0')
	{
		ft_selected(i);
		if (str[i] != '\n')
			ft_putchar(str[i]);
		x++;
		if (x == ts.ws_col || str[i] == '\n')
		{
			y = ft_getcurpos();
			if (y >= ts.ws_row)
				p++;
			if (x == ts.ws_col)
			{
				ft_cursmove('d', 1);
				ft_putterm("cr");
			}
			else if (str[i] == '\n')
			{
				ft_putchar(str[i]);
			}
			x = 0;
		}
		i++;
	}
	return (p);
}

int			ft_promptlen(void)
{
	if (g_input_type == PROMPT)
		return (PROMPTLINE);
	if (g_input_type == SQ)
		return (QPROMPT);
	if (g_input_type == DQ)
		return (DQPROMPT);
	if (g_input_type == BQ)
		return (BQPROMPT);
	if (g_input_type == BS)
		return (BSPROMPT);
	if (g_input_type == PIPE)
		return (PIPEPROMPT);
	if (g_input_type == HERDOC)
		return (HERDOCPROMPT);
	return (0);
}

int	ft_lastbackline(int p)
{
	if (!ft_strnstr(g_input, "\n", p) &&  g_input[p] == '\n')
		return (1);
	return (0);
}

int ft_lastlinereturn(int x, int col, int p, int pos)
{
	if (p >= col)
		return (x - 1);
	else
		return ((ft_lastbackline(pos - 1) ? x - 1 : x));
}

int	ft_getlinelen(int y)
{
	int i;
	struct winsize ts;
	t_cursor cursor;
	int prompt;
	int p;

	i = 0;
	ts = ft_winsize();
	prompt = ft_promptlen();
	cursor = ft_defaultcursor(&cursor);
	while (g_input[i] != '\0')
	{
		p = (cursor.y == 0) ? cursor.x + prompt : cursor.x;
		if (p >= ts.ws_col - 1 || g_input[cursor.pos - 1] == '\n')
		{
			if (cursor.y == y)
				return (ft_lastlinereturn(cursor.x, ts.ws_col, p, cursor.pos));
			cursor.x = 0;
			cursor.y++;
		}
		else
			cursor.x++;
		cursor.pos++;
		i++;
	}
	cursor.x += cursor.y;
	return ((cursor.x >= 0) ? cursor.x : 0);
}

t_cursor	ft_curright(t_cursor cur, int i)
{
	int j;
	struct winsize ts;
	int prompt;
	int p;

	j = 0;
	ts = ft_winsize();
	prompt = ft_promptlen();
	while (j < i)
	{
		cur.pos++;
		cur.x++;
		p = (cur.y == 0) ? cur.x + prompt : cur.x;
		if (p >= ts.ws_col || g_input[cur.pos - 1] == '\n')
		{
			cur.x = 0;
			cur.y++;
		}
		j++;
	}
	return (cur);
}

t_cursor	ft_curleft(t_cursor cur, int i)
{
	int j;
	int prompt;
	struct winsize ts;

	j = 0;
	ts = ft_winsize();
	prompt = ft_promptlen();
	while (j < i)
	{
		if (cur.x < 0 && cur.y == 0)
			break ;
		cur.pos--;
		cur.x--;
		if (cur.x < 0 && cur.y > 0)
		{
			cur.y--;
			cur.x = ft_getlinelen(cur.y);
		}
		j++;
	}
	return (cur);
}

void	ft_current_cursor(t_cursor g_cursor)
{
	ft_cursmove('d', g_cursor.y);
	ft_cursmove('r', g_cursor.x);
}

void ft_termmanager(char *g_input, t_cursor g_cursor)
{
	int y;

	y = 0;
	ft_putterm("rc");
	ft_putterm("sc");
	ft_putterm("cd");
	if (g_input)
		y = ft_showstr(g_input);
	ft_putterm("rc");
	ft_cursmove('u', y);
	ft_putterm("sc");
	ft_current_cursor(g_cursor);
}

char		*readline2(char **history)
{
	int	key;
	int i;

	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_cpy();
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_readx())) != ENTRE)
	{
		if (g_input_type == PROMPT)
			break ;
		if (ft_checkkey(key))
		{
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
			doctrld(key, 0);
		}
		ft_termmanager(g_input, g_cursor);
	}
	if (g_input_type == PROMPT)
	{
		ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	g_input = ft_straddchr(g_input, '\n');
	ft_cancel();
	return (g_input);
}

char		*readline3(char **history, int *x)
{
	int	key;
	int i;

	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_cpy();
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_readx())) != ENTRE)
	{
		if (g_input_type == PROMPT)
			break ;
		if (ft_checkkey(key))
		{
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
			doctrld(key, 0);
		}
		ft_termmanager(g_input, g_cursor);
	}
	if (!ft_strisprint(g_input) || g_input_type == PROMPT)
	{
		if (g_input_type == PROMPT)
			*x = 1;
		ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	ft_cancel();
	ft_putchar('\n');
	return (g_input);
}

char		*readline4(char **history, int *x)
{
	int	key;
	int i;

	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_cpy();
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_readx())) != ENTRE)
	{
		if (g_input_type == PROMPT)
			break ;
		if (ft_checkkey(key))
		{
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
			doctrld(key, 0);
		}
		ft_termmanager(g_input, g_cursor);
	}
	if (g_input_type == PROMPT)
	{
		*x = 1;
		ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	ft_cancel();
	ft_putchar('\n');
	return (g_input);
}

char		*readline(char **history)
{
	int	key;
	int i;

	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_cpy();
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_readx())) != ENTRE)
	{
		if (ft_checkkey(key))
		{
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
			if (doctrld(key, 1))
				break;
		}
		ft_termmanager(g_input, g_cursor);
	}
	ft_cpy();
	if (!ft_strisprint(g_input))
	{
		ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	ft_cancel();
	ft_putchar('\n');
	return (g_input);
}


char	**ft_addtotab(char **tabl, char *str)
{
	int i;
	int len;
	char **new;

	i = 0;
	len = ft_tablen(tabl) + 1;
	SAFE(new = (char **)malloc(sizeof(char*) * (len + 1)));
	while (tabl[i] != NULL)
	{
		new[i] = tabl[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[++i] = NULL;
	free(tabl);
	return (new);
}

void		ft_shell(void)
{
	char			*input;
	char			**cmds;
	char			**history;

	if (!(history = (char **)malloc(sizeof(char*))))
		return ;
	while (1)
	{
		ft_prompt();
		g_input_type = PROMPT;
		ft_term_prepare(0);
		if (!(input = ft_strdup(readline(history))) || parseerror(input, 1))
		{
			ft_strdel(&g_input);
			continue ;
		}
		ft_strdel(&g_input);
		if (!(input = makecmdclear(input, history)))
			continue ;
		ft_term_prepare(1);
		history = ft_addtotab(history, input);
		if (!((cmds = createcmds(input))))
			continue ;
		if (ft_putcmds(cmds, history))
			break ;
		ft_endinput(cmds, input);
	}
	ft_endinput(cmds, input);
	ft_freetable(&history);
}
