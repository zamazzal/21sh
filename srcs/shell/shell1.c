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

static int	ft_checkkey(int c)
{
	if (c == 10)
		return (0);
	if (c == 4)
		return (-1);
	return (c);
}

char		*readline2(char **history)
{
	int	key;
	int	pos;
	int i;

	g_input = ft_prepareinput();
	pos = 0;
	i = ft_tablen(history) - 1;
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			pos += ft_straddchrinpos(key, pos);
		else
			pos = ft_checknoprint(key, pos, history, &i);
	}
	if (key == -1)
	{
		if (key == -1)
			ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	ft_straddchr(g_input, '\n');
	return (g_input);
}

void		ft_showcmd(int key, int pos, char *cmd)
{
	if (key == BACKSPACE && pos < -1)
		return ;
	ft_putterm("cr");
	ft_putterm("cd");
	ft_prompt();
	ft_putstr(cmd);
}

void		ft_termmanager(int key, int pos, char *g_input)
{
	if (key != LEFT && key != RIGHT)
		ft_showcmd(key, pos, g_input);
}

char		*readline(char **history)
{
	int	key;
	int	pos;
	int i;

	SAFE(g_input = ft_prepareinput());
	pos = -1;
	i = ft_tablen(history) - 1;
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			pos += ft_straddchrinpos(key, pos + 1);
		else
			pos = ft_checknoprint(key, pos, history, &i);
		ft_termmanager(key, pos, g_input);
	}
	ft_putchar('\n');
	if (key == -1 || !ft_strisprint(g_input))
	{
		if (key == -1)
			ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
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
		g_input_type = 1;
		ft_term_prepare(0);
		if (!(input = readline(history)) || parseerror(input, 1))
			continue ;
		history = ft_addtotab(history, input);
		input = makecmdclear(input, history);
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
