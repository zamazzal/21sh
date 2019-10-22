/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:51:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/27 13:52:31 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		ft_cancel(void)
{
	ft_putterm("rc");
	g_cursor = ft_defaultcursor(&g_cursor);
	g_cursor.pos = ft_strlen(g_input);
	g_cursor = ft_curright(g_cursor, g_cursor.pos);
	ft_current_cursor(g_cursor);
}

void		ft_signal(int x)
{
	if (x == SIGINT && g_pid == 0)
	{
		ft_cancel();
		ft_putchar('\n');
		g_cursor = ft_defaultcursor(&g_cursor);
		if (g_input_type == PROMPT)
			ft_prompt();
		else if (g_input_type == BS)
			ft_putstr("> ");
		else if (g_input_type == DQ)
			ft_putstr("dquote> ");
		else if (g_input_type == SQ)
			ft_putstr("quote> ");
		else if (g_input_type == BQ)
			ft_putstr("bquote> ");
		else if (g_input_type == PIPE)
			ft_putnstr("pipe> ", g_pipe);
		ft_strclr(g_input);
		ft_putterm("sc");
	}
	if (g_pid == 1)
		ft_putchar('\n');
}

void		ft_winch(int x)
{
	if (x == SIGWINCH && g_pid == 0)
	{
		ft_termmanager(g_input, g_cursor);
	}
}