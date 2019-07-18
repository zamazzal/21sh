/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:16:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/16 15:16:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int	ft_checkquote(char *cmd)
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

	input = ft_strnew(BUFFER_SIZE);
	while ((r = ft_checkquote(cmd)))
	{
		if (r == DQ)
			ft_putstr("dquote> ");
		else if (r == SQ)
			ft_putstr("quote> ");
		else if (r == '`')
			ft_putstr("bquote> ");
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0))
			continue ;
		cmd = ft_strjoin_lite(cmd, input);
	}
	cmd = ft_removeantin(cmd);
	ft_strdel(&input);
	return (cmd);
}