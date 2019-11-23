/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:17:03 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:18:32 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	ft_lastbackline(int p)
{
	if (!ft_strnstr(g_input, "\n", p) && g_input[p] == '\n')
		return (1);
	return (0);
}

static int	ft_lreturn(int x, int col, int p, int pos)
{
	if (p >= col)
		return (x - 1);
	else
		return ((ft_lastbackline(pos - 1) ? x - 1 : x));
}

static void	ft_setvars(struct winsize *ts, int *prompt, t_cursor *cursor)
{
	*ts = ft_winsize();
	*prompt = ft_promptlen();
	*cursor = ft_defaultcursor(cursor);
}

int			ft_getlinelen(int y)
{
	int				i;
	struct winsize	ts;
	t_cursor		cursor;
	int				prompt;
	int				p;

	i = 0;
	ft_setvars(&ts, &prompt, &cursor);
	while (g_input[i] != '\0')
	{
		p = (cursor.y == 0) ? cursor.x + prompt : cursor.x;
		if (p >= ts.ws_col - 1 || g_input[cursor.pos - 1] == '\n')
		{
			if (cursor.y == y)
				return (ft_lreturn(cursor.x, ts.ws_col, p, cursor.pos));
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
