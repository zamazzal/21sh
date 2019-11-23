/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:00:42 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/21 17:05:43 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_execctrld_her(int pos, int *x)
{
	if (!g_input)
	{
		*x = 2;
		return (1);
	}
	if (g_input[pos] != '\0')
		ft_strcpy(&g_input[pos], &g_input[pos + 1]);
	if (g_input[0] == '\0')
		ft_strdel(&g_input);
	return (0);
}

static int	heredoc_ctrld(int key, int *x)
{
	if (key == CTRLD)
	{
		ft_cpy();
		ft_clearbuffer();
		if (ft_execctrld_her(g_cursor.pos, x))
			return (1);
	}
	return (0);
}

char		*readline5(char **history, int *x)
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
			if (heredoc_ctrld(key, x))
				break ;
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
