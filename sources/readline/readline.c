/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:19:38 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:20:10 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char		*readline2(char **history)
{
	int	key;
	int i;

	ft_preparereadline(&i, history);
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

	ft_preparereadline(&i, history);
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
	ft_canelwithn();
	return (g_input);
}

char		*readline4(char **history, int *x)
{
	int	key;
	int i;

	ft_preparereadline(&i, history);
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
	ft_canelwithn();
	return (g_input);
}

char		*readline(char **history)
{
	int	key;
	int i;

	ft_preparereadline(&i, history);
	while ((key = ft_checkkey(ft_readx())) != ENTRE)
	{
		if (ft_checkkey(key))
		{
			g_cursor = ft_checknoprint(key, g_cursor, history, &i);
			if (doctrld(key, 1))
				break ;
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
	ft_canelwithn();
	return (g_input);
}
