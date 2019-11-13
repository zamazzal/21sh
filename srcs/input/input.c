/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:47:54 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/22 21:45:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static size_t		ft_getindex(char *str, char c)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}

char				*ft_removeantin(char *str)
{
	int r;

	if ((r = ft_getindex(str, '\n')) > 0)
		str = ft_strsub_lite(str, 0, r);
	return (str);
}

int					ft_checkcmdform(char *cmd)
{
	if (ft_checkquote(cmd))
		return (1);
	if (ft_checkpipe(cmd))
		return (2);
	if (ft_checkbackslash(cmd))
		return (3);
	return (0);
}

char				*makecmdclear(char *cmd, char **history)
{
	int x;
	int r;

	x = 0;
	while ((r = ft_checkcmdform(cmd)))
	{
		if (x == 0 && r == 1)
			cmd = ft_straddchr(cmd, '\n');
		if (r == 1)
		{
			if (!(cmd = ft_closequotes(cmd, history)))
				return (NULL);
		}
		if (r == 2)
		{
			if (!(cmd = ft_closepipe(cmd, history)))
				return (NULL);
		}
		if (r == 3)
		{
			if (!(cmd = ft_endbackslash(cmd, history)))
				return (NULL);
		}
		x++;
	}
	return (cmd);
}
