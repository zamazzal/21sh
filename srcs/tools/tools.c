/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 11:47:52 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/12 11:48:16 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		ft_tablen(char **array)
{
	int len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return(len);
}

void	ft_freelistes(t_subcmds *cmds)
{
	t_subcmds *backup;

	while (cmds != NULL)
	{
		backup = cmds;
		cmds = cmds->next;
		free(backup->cmd);
		free(backup);
	}
}

void	ft_freexlistes(t_cmds *cmds)
{
	t_cmds *backup;
	while (cmds != NULL)
	{
		ft_freelistes(cmds->cmds);
		backup = cmds;
		cmds = cmds->next;
		free(backup);
	}
}

void			ft_freetable(char **array)
{
	int i;

	i = 0;
	if (*array)
	{
		while (array[i] != NULL)
			ft_strdel(&array[i++]);
		free(array);
	}
}
