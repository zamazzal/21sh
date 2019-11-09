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
	g_cursor = ft_curright(g_cursor, ft_strlen(g_input));
	ft_current_cursor(g_cursor);
}

void		ft_signal(int x)
{
	if (x == SIGINT && g_pid == 0)
	{
		ft_cancel();
		g_cursor = ft_defaultcursor(&g_cursor);
		if (g_input_type == PROMPT)
		{
			ft_putchar('\n');
			ft_prompt();
		}
		else {
			ioctl(0, TIOCSTI, "\12");
			g_input_type = PROMPT;
		}
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