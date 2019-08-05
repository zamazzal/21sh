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

char		*readline2(void)
{
	int	key;
	int	pos;

	g_input = ft_prepareinput();
	pos = 0;
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			pos += ft_straddchrinpos(key, pos);
		else
			pos = ft_checknoprint(key, pos);
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

char		*readline(void)
{
	int	key;
	int	pos;

	SAFE(g_input = ft_prepareinput());
	pos = -1;
	while ((key = ft_checkkey(ft_getch())) > 0)
	{
		if (ft_isprint(key))
			pos += ft_straddchrinpos(key, pos + 1);
		else
			pos = ft_checknoprint(key, pos);
	}
	if (key == -1 || !ft_strisprint(g_input))
	{
		if (key == -1)
			ft_putchar('\n');
		ft_strdel(&g_input);
		return (NULL);
	}
	return (g_input);
}

void		ft_shell(void)
{
	char			*input;
	char			**cmds;

	while (1)
	{
		ft_prompt();
		g_input_type = 1;
		if (!(input = readline()) || parseerror(input, 1))
			continue ;
		input = makecmdclear(input);
		if (!((cmds = createcmds(input))))
			continue ;
		if (ft_strequ(input, "exit"))
			break ;
		ft_putcmds(cmds);
		ft_endinput(cmds, input);
	}
	ft_endinput(cmds, input);
}
