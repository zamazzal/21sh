/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:15:57 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/16 15:15:58 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_checkpipe(char *cmd)
{
	int i;
	int len;
	int c;

	len = ft_strlen(cmd) - 1;
	i = 0;
	c = 0;
    if (len >= 0 && cmd[len] == ';')
        len--;
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

char	*ft_closepipe(char *cmd)
{
	int		r;
	char	*input;
	int		n;

	input = ft_strnew(BUFFER_SIZE);
	n = 1;
	while ((r = ft_checkpipe(cmd)))
	{
		ft_putnstr("pipe> ", n);
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || !ft_strisprint(input))
			continue ;
		n++;
		input = ft_removeantin(input);
		cmd = ft_strjoin_lite(cmd, input);
	}
	ft_strdel(&input);
	return (cmd);
}