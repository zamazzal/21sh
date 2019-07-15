/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 20:20:09 by zamazzal          #+#    #+#             */
/*   Updated: 2019/07/12 20:20:27 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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