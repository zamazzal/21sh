/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:16:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/22 21:45:02 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_checkquote(char *cmd)
{
	int		i;
	char	c;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == DQ || cmd[i] == SQ || cmd[i] == '`')
		{
			c = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != c)
				i++;
			if (cmd[i] == '\0')
				return (c);
		}
		i++;
	}
	return (0);
}

char	*ft_closequotes(char *cmd, char **history)
{
	int		r;

	while ((r = ft_checkquote(cmd)))
	{
		g_cursor = ft_defaultcursor(&g_cursor);
		ft_putterm("cr");
		if (r == DQ)
			ft_putstr("dquote> ");
		else if (r == SQ)
			ft_putstr("quote> ");
		else if (r == BQ)
			ft_putstr("bquote> ");
		g_input_type = r;
		if (!(g_input = readline2(history)))
		{
			ft_strdel(&cmd);
			return (NULL);
		}
		cmd = ft_strjoin_lite(cmd, g_input);
		ft_strdel(&g_input);
	}
	cmd = ft_removeantin(cmd);
	return (cmd);
}
