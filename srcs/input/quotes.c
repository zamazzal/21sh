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

char	*ft_closequotes(char *cmd)
{
	int		r;
	char	*input;

	while ((r = ft_checkquote(cmd)))
	{
		if (r == DQ)
			ft_putstr("dquote> ");
		else if (r == SQ)
			ft_putstr("quote> ");
		else if (r == BQ)
			ft_putstr("bquote> ");
		g_input_type = r;
		if (!(input = readline2()))
			continue ;
		cmd = ft_strjoin_lite(cmd, input);
		ft_strdel(&input);
	}
	cmd = ft_removeantin(cmd);
	return (cmd);
}
