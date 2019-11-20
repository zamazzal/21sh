/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 21:15:28 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 16:09:45 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int		ft_redirsub(char *cmd, int r)
{
	char	**cmds;
	int		i;
	int		rzlt;

	SAFE(cmds = ft_cmdsplit(cmd, '|'));
	i = 0;
	while (cmds[i] != NULL)
	{
		r = (cmds[i + 1]) ? 2 : r;
		rzlt = check_reds(cmds[i], r);
		if (rzlt == 0)
		{
			ft_freetable(&cmds);
			return (1);
		}
		i++;
	}
	ft_freetable(&cmds);
	return (0);
}

int				ft_redirerror(char *cmd)
{
	char	**cmds;
	int		i;
	int		r;

	SAFE(cmds = ft_cmdsplit(cmd, ';'));
	i = 0;
	while (cmds[i] != NULL)
	{
		r = (cmds[i + 1]) ? 1 : 0;
		if (r == 0)
			r = (ft_checkcinstr(cmd, ';')) ? 1 : 0;
		if (ft_redirsub(cmds[i], r))
		{
			ft_freetable(&cmds);
			return (1);
		}
		i++;
	}
	ft_freetable(&cmds);
	return (0);
}

char			**createcmds(char *input)
{
	char	**cmds;

	SAFE(cmds = ft_cmdsplit(input, ';'));
	if (ft_checkcmds(cmds))
	{
		ft_strdel(&input);
		ft_freetable(&cmds);
		return (NULL);
	}
	return (cmds);
}
