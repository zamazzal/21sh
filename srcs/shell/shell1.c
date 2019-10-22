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

void		ft_showstr(char *str)
{
	int i;
	int x;
	struct winsize ts;

	i = 0;
	x = ft_promptlen();
	ts = ft_winsize();
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		x++;
		if (x == ts.ws_col - 1)
		{
			x = 0;
			ft_cursmove('d', 1);
			ft_putterm("cr");
		}
		i++;
	}
}

int		ft_getstrlen(char *str)
{
	int x;
	int len;
	int prompt;
	struct winsize ts;

	len = ft_strlen(str);
	ts = ft_winsize();
	prompt = ft_promptlen();
	x = (len + prompt + ((len + prompt) / (ts.ws_col))) / (ts.ws_col);
	return (x);
}

int		ft_readshow(char *cmd)
{
	ft_putterm("cd");
	ft_showstr(cmd);
	return (0);
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
		cur.x++;
		cur.pos++;
		p = (cur.y == 0) ? cur.x + prompt : cur.x;
		if (p >= ts.ws_col - 1 || g_input[cur.pos] == '\n')
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
		cur.pos--;
		if (cur.x == 0 && cur.y == 0)
			break ;
		cur.x--;
		if (cur.x == 0 && cur.y > 0)
		{
			cur.y--;
			cur.x = (cur.y == 0) ? (ts.ws_col - 1) - prompt : (ts.ws_col - 1);
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
	ft_putterm("rc");
	ft_putterm("sc");
	ft_readshow(g_input);
	ft_putterm("rc");
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

	history = (char **)malloc(sizeof(char*));
	while (1)
	{
		ft_prompt();
		g_input_type = PROMPT;
		ft_term_prepare(0);
		if (!(input = readline(history)) || parseerror(input, 1))
			continue ;
		input = makecmdclear(input, history);
		history = ft_addtotab(history, input);
		if (!((cmds = createcmds(input))))
			continue ;
		ft_term_prepare(1);
		if (ft_putcmds(cmds))
			break ;
		ft_endinput(cmds, input);
	}
	ft_endinput(cmds, input);
	ft_freetable(&history);
}
