/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:15:51 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/16 15:15:54 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_checkbackslash(char *cmd)
{
	int i;
	int len;

	len = ft_strlen(cmd) - 1;
	i = 0;
	if (cmd[len] == '\\')
	{
		while (cmd[len] == '\\')
		{
			len--;
			i++;
		}
	}
	if (i % 2 == 0 || i == 0)
		return (0);
	return (1);
}

char	*ft_endbackslash(char *cmd)
{
	int		r;
	char	*input;
	int		len;

	input = ft_strnew(BUFFER_SIZE);
	while ((r = ft_checkbackslash(cmd)))
	{
		ft_putstr("> ");
		ft_strclr(input);
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || !ft_strisprint(input))
			continue ;
		len = ft_strlen(cmd);
		if (len > 1)
			cmd = ft_strjoin_lite(ft_strsub_lite(cmd, 0, len - 1), input);
		else
		{
			ft_strdel(&cmd);
			cmd = ft_strdup(input);
		}
		cmd = ft_removeantin(cmd);
	}
	ft_strdel(&input);
	return (cmd);
}