/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:22:29 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:23:19 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_promptlen(void)
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
	if (g_input_type == HERDOC)
		return (HERDOCPROMPT);
	return (0);
}

void	ft_preparereadline(int *i, char **history)
{
	g_cursor = ft_defaultcursor(&g_cursor);
	*i = ft_tablen(history) - 1;
	ft_cpy();
	ft_putterm("sc");
}

void	ft_canelwithn(void)
{
	ft_cancel();
	ft_putchar('\n');
}
