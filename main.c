/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/07/11 20:07:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	ft_putlistes(t_subcmds *cmds)
{
	ft_putendl("-------*start*-------");
	while (cmds != NULL)
	{
		ft_putendl(cmds->cmd);
		cmds = cmds->next;
	}
	ft_putendl("-------*end*-------");
}

void	ft_putxlistes(t_cmds *cmds)
{
	while (cmds != NULL)
	{
		ft_putlistes(cmds->cmds);
		cmds = cmds->next;
	}
}

int main(int argc, char **argv)
{
	t_cmds	*mycmds;
	char **cmds;

	if (argc > 1)
	{
		if (parseerror(argv[1]))
			return (1);
		if (!(cmds = ft_cmdsplit(argv[1], ';')))
			return (1);
		mycmds = splitcmds(cmds);
		ft_freetable(cmds);
		ft_putxlistes(mycmds);
		ft_freexlistes(mycmds);
	}
	return (0);
}
