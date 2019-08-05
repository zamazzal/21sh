/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/07/27 15:20:26 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int				ft_checkred(char *cmd)
{
	if (ft_checkcinstr(cmd, '<'))
		return (1);
	if (ft_checkcinstr(cmd, '>'))
		return (1);
	return (0);
}

static void		ft_putcmd(char *cmd)
{
	char **cmds;
	int i;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return ;
	i = 0;
	while (cmds[i] != NULL)
	{
		if (ft_checkred(cmds[i]))
		{
			ft_putendl(cmds[i]);
		}
		/*if (cmds[i + 1] != NULL)
		{
			//pipe!
		}*/

		i++;
	}
	ft_freetable(cmds);
}

void			ft_putcmds(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i] != NULL)
	{
		ft_putcmd(cmd[i]);
		i++;
	}
}

static char		**creation(char **table)
{
	int		i;
	char	**new;

	g_pid = 0;
	i = 0;
	SAFE(new = (char **)malloc(sizeof(char *) * (ft_tablen(table) + 1)));
	while (table[i] != NULL)
	{
		new[i] = ft_strdup(table[i]);
		i++;
	}
	table[i] = NULL;
	return (new);
}

int				main(void)
{
	extern char		**environ;

	if (ft_tinit() == -1 || ft_checktitty())
		return (0);
	signal(SIGINT, ft_signal);
	SAFE(g_environ = creation(environ));
	g_input_type = 0;
	ft_term_prepare(0);
	ft_shell();
	ft_term_prepare(1);
	ft_freetable(g_environ);
	return (1);
}
