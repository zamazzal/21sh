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

void		ft_signal(int x)
{
	if (x == SIGINT && g_pid == 0)
	{
		ft_putchar('\n');
		if (g_input_type == 1)
			ft_prompt();
		else if (g_input_type == 10)
			ft_putstr("> ");
		else if (g_input_type == DQ)
			ft_putstr("dquote> ");
		else if (g_input_type == SQ)
			ft_putstr("quote> ");
		else if (g_input_type == BQ)
			ft_putstr("bquote> ");
		else if (g_input_type == 20)
			ft_putnstr("pipe> ", g_pipe);
		ft_strclr(g_input);
	}
	if (g_pid == 1)
		ft_putchar('\n');
}