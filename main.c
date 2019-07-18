/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/07/15 19:54:15 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

char *ft_prepareinput(void)
{
	char			*input;

	input = ft_strnew(BUFFER_SIZE);
	ft_putstr("21sh $> ");
	ft_strclr(input);
	return (input);
}

void	ft_endinput(char **cmds,char *input)
{
	ft_freetable(cmds);
	ft_strdel(&input);
}

char	**createcmds(char *input)
{
	char	**cmds;

	SAFE(cmds = ft_cmdsplit(input, ';'));
	if (ft_checkcmds(cmds))
	{
		ft_strdel(&input);
		ft_freetable(cmds);
		return (NULL);
	}
	return (cmds);
}

void	ft_putcmd(char *cmd)
{
	char **cmds;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return ;
	ft_puttables(cmds);
}

void	ft_putcmds(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i] != NULL)
	{
		ft_putendl("====START====");
		ft_putcmd(cmd[i]);
		ft_putendl("====END====");
		i++;
	}
}

void	ft_shell(void)
{
	int				r;
	char			*input;
	char			**cmds;

	while (1)
	{
		input = ft_prepareinput();
		if (((r = read(0, input, BUFFER_SIZE)) <= 0) || ft_inputerror(input, 1))
		{
			if (r == 0)
				ft_putchar('\n');
			ft_strdel(&input);
			continue ;
		}
		input = makecmdclear(input);
		if (!((cmds = createcmds(input))))
			continue ;
		if (ft_strequ(input, "exit"))
			break ;
		ft_putcmds(cmds);
		ft_endinput(cmds, input);
	}
	ft_endinput(cmds, input);
}

static void		ft_signal(int x)
{
	if (x == SIGINT && g_pid == 0)
	{
		ft_putchar('\n');
		ft_putstr("21sh $> ");
	}
	if (g_pid == 1)
		ft_putchar('\n');
}

static char		**creation(char **tab)
{
	int		i;
	char	**new;

	g_pid = 0;
	i = 0;
	signal(SIGINT, ft_signal);
	SAFE(new = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1)));
	while (tab[i] != NULL)
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (new);
}

int		main(void)
{
	extern char		**environ;

	g_environ = creation(environ);
	ft_shell();
	return (0);
}
