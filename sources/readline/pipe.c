/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:15:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 16:38:12 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_checkpipe(char *cmd)
{
	int i;
	int len;
	int c;

	len = ft_strlen(cmd) - 1;
	len = (len >= 0 && cmd[len] == ';') ? len - 1 : len;
	i = 0;
	c = 0;
	while (len >= 0 && (cmd[len] < 31 || cmd[len] == '|'))
	{
		if (cmd[len] == '|')
		{
			c = 1;
			len--;
			while (len >= 0 && cmd[len] == '\\')
			{
				len--;
				i++;
			}
		}
		len--;
	}
	if ((i % 2 == 0 || i == 0) && c == 1)
		return (1);
	return (0);
}

char	*ft_closepipe(char *cmd, char **history)
{
	int	r;
	int x;

	g_pipe = 1;
	x = 0;
	while ((r = ft_checkpipe(cmd)))
	{
		ft_putnstr("pipe> ", g_pipe);
		g_input_type = PIPE;
		if (!(g_input = readline3(history, &x)))
		{
			if (x == 1)
			{
				ft_strdel(&cmd);
				return (NULL);
			}
			continue ;
		}
		g_pipe++;
		g_input = ft_removeantin(g_input);
		cmd = ft_strjoin_lite(cmd, g_input);
		ft_strdel(&g_input);
	}
	return (cmd);
}
