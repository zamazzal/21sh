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

void	ft_freecmds(t_cmds *cmds)
{
	t_subcmds	*cmd;
	t_subcmds	*backup;
	t_cmds		*zbackup;

	while (cmds != NULL)
	{
		cmd = cmds->cmds;
		while(cmd != NULL)
		{
			backup = cmd;
			cmd = cmd->next;
			free(backup);
		}
		zbackup = cmds;
		cmds = cmds->next;
		free(zbackup);
	}
}

int		ft_checkc(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_subcmds	*putcommand(char **cmds)
{
	t_subcmds	*scmds;
	t_subcmds	*first;
	int j;

	j = 0;
	if (!(scmds = (t_subcmds*)malloc(sizeof(t_subcmds))))
		return (NULL);
	first = scmds;
	scmds->cmd = ft_strdup(cmds[j]);
	scmds->next = NULL;
	while (cmds[++j] != NULL)
	{
		if (!(scmds->next = (t_subcmds*)malloc(sizeof(t_subcmds))))
			return (NULL);
		scmds = scmds->next;
		scmds->cmd = ft_strdup(cmds[j]);
		scmds->next = NULL;
	}
	ft_freetable(cmds);
	return (first);
}

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

t_cmds	*splitcmds(char **array)
{
	t_cmds		*first;
	t_cmds		*mcmds;
	char		**cmds;
	int			i;
	int			j;
	i = 0;
	if (!(mcmds = (t_cmds*)malloc(sizeof(t_cmds))))
		return (NULL);
	if (!(cmds = ft_cmdsplit(array[i], '|')))
		return (NULL);
	first = mcmds;
	mcmds->cmds = putcommand(cmds);
	mcmds->next = NULL;
	while (array[++i] != NULL)
	{
		if (!(cmds = ft_cmdsplit(array[i], '|')))
			return (NULL);
		if (!(mcmds->next = (t_cmds*)malloc(sizeof(t_cmds))))
			return (NULL);
		mcmds = mcmds->next;
		mcmds->cmds = putcommand(cmds);
		mcmds->next = NULL;
	}
	return (first);
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
