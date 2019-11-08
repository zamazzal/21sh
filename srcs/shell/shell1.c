/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:48:31 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/27 21:38:33 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_getch(void)
{
	int key;

	key = 0;
	read(0, &key, sizeof(int));
	return (key);
}

t_cursor	ft_defaultcursor(t_cursor *cursor)
{
	(*cursor).pos = 0;
	(*cursor).x = 0;
	(*cursor).y = 0;
	return (*cursor);
}

static int	ft_checkkey(int c)
{
	if (c == 10)
		return (0);
	if (c == 4)
		return (-1);
	return (c);
}

struct winsize	ft_winsize(void)
{
	struct winsize ts;

    ioctl(0, TIOCGWINSZ, &ts);
	return (ts);
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

int		ft_readshow(char *cmd)
{
	ft_putterm("cd");
	return (ft_showstr(cmd));
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
	y = ft_readshow(g_input);
	ft_putterm("rc");
	ft_cursmove('u', y);
	ft_putterm("sc");
	ft_current_cursor(g_cursor);
}

char		*readline2(char **history)
{
	int	key;
	int i;

	SAFE(g_input = ft_prepareinput());
	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			g_cursor = ft_straddchrinpos(key, g_cursor);
		else
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
		ft_termmanager(g_input, g_cursor);
	}
	if (key == -1)
	{
		if (key == -1)
			ft_cancel();
		ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	ft_straddchr(g_input, '\n');
	ft_cancel();
	return (g_input);
}

char		*readline(char **history)
{
	int	key;
	int i;

	SAFE(g_input = ft_prepareinput());
	g_cursor = ft_defaultcursor(&g_cursor);
	i = ft_tablen(history) - 1;
	ft_putterm("sc");
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			g_cursor = ft_straddchrinpos(key, g_cursor);
		else
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
		ft_termmanager(g_input, g_cursor);
	}
	if (key == -1 || !ft_strisprint(g_input))
	{
		if (key == -1)
			ft_cancel();
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
		if (!(input = readline(history)) || parseerror(input, 1))
			continue ;
		input = makecmdclear(input, history);
		ft_term_prepare(1);
		history = ft_addtotab(history, input);
		if (!((cmds = createcmds(input))))
			continue ;
		if (ft_putcmds(cmds))
			break ;
		ft_endinput(cmds, input);
	}
	ft_endinput(cmds, input);
	ft_freetable(&history);
}
