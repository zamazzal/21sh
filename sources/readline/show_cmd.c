/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:15:37 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 18:49:20 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void		ft_selected(int i)
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

static void		ft_innewline(int *p, int *x, char c, struct winsize ts)
{
	int y;

	y = ft_getcurpos();
	if (y >= ts.ws_row)
		*p += 1;
	if (*x == ts.ws_col)
	{
		ft_cursmove('d', 1);
		ft_putterm("cr");
	}
	else if (c == '\n')
	{
		ft_putchar(c);
	}
	*x = 0;
}

static int		ft_showstr(char *str)
{
	int				i;
	int				x;
	struct winsize	ts;
	int				p;

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
			ft_innewline(&p, &x, str[i], ts);
		i++;
	}
	return (p);
}

void			ft_current_cursor(t_cursor g_cursor)
{
	ft_cursmove('d', g_cursor.y);
	ft_cursmove('r', g_cursor.x);
}

void			ft_termmanager(char *g_input, t_cursor g_cursor)
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
