/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:15:51 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/18 16:55:25 by zamazzal         ###   ########.fr       */
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

static char		*ft_returnnull(char *cmd)
{
	ft_strdel(&cmd);
	return (NULL);
}

static char		*changecontent(char *cmd)
{
	ft_strdel(&cmd);
	cmd = ft_strdup(g_input);
	return (cmd);
}

char			*ft_endbackslash(char *cmd, char **history)
{
	int	r;
	int	len;
	int x;

	x = 0;
	while ((r = ft_checkbackslash(cmd)))
	{
		ft_putstr("> ");
		g_input_type = BS;
		if (!(g_input = readline4(history, &x)))
		{
			if (x == 1)
				return (ft_returnnull(cmd));
			continue ;
		}
		len = ft_strlen(cmd);
		if (len > 1)
			cmd = ft_strjoin_lite(ft_strsub_lite(cmd, 0, len - 1), g_input);
		else
			cmd = changecontent(cmd);
		ft_strdel(&g_input);
	}
	return (cmd);
}
