/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:45 by aihya             #+#    #+#             */
/*   Updated: 2019/09/16 19:57:36 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		**ctables(char **array)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			len = ft_strlen(array[i]);
			if (array[i][0] == SQ && array[i][len - 1] == SQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == DQ && array[i][len - 1] == DQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			else if (array[i][0] == BQ && array[i][len - 1] == BQ)
				array[i] = ft_strsub_lite(array[i], 1, len - 2);
			i++;
		}
		return (array);
	}
	return (NULL);
}

int				ft_checkred(char *cmd)
{
	if (ft_checkcinstr(cmd, '<'))
		return (1);
	if (ft_checkcinstr(cmd, '>'))
		return (1);
	return (0);
}

int **ft_createpipes(int piplen)
{
	int i;
	int **pipes;

	SAFE(pipes = (int **)malloc(sizeof(int*) * piplen));
	i = 0;
	while (i < piplen)
	{
		SAFE(pipes[i] = (int *)malloc(sizeof(int) * 2));
		if (pipe(pipes[i]) == -1)
		{
			ft_puterror("pipe error");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void			ft_closepipes(int **pipes, int piplen)
{
	int i;

	i = 0;
	while (i < piplen)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int			putcmd(char **cmd, int i, t_info info)
{
	char **argv;

	argv = ms_parse(cmd[i]);
	if (!(ft_builtins(ctables(argv), info)))
	{
		ft_freetable(&cmd);
		ft_freetable(&argv);
		return (1);
	}
	ft_freetable(&argv);
	return (0);
}

void		ft_inputdone(int fd)
{
	dup2(fd, 0);
	close(fd);
}

int		ft_pipe(int *fd)
{
	int p[2];

	if (pipe(p) == -1)
		return (-1);
	*fd = p[0];
	dup2(p[1], 1);
	close(p[1]);
	return (p[1]);
}

void			ft_waitpids(void)
{
	int r;

	r = wait(NULL);
	while (r > 0)
		r = wait(NULL);
}

void			ft_endcmds(char **cmds, int fd)
{
	dup2(fd, 0);
	ft_waitpids();
	g_pid = 0;
	ft_freetable(&cmds);
}

static int		ft_putcmd(char *cmd)
{
	char **cmds;
	int i;
	int f[2];
	int p[2];
	t_info	info;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return (1);
	i = 0;
	f[0] = dup(0);
	f[1] = dup(1);
	info.fd = -1;
	info.mode = (ft_tablen(cmds) > 1) ? 1 : 0;
	while (cmds[i] != NULL)
	{
		if (ft_checkred(cmds[i]))
		{
			ft_putendl(cmds[i++]);
			continue;
		}
		if (i > 0)
			ft_inputdone(p[0]);
		if (cmds[i + 1] != NULL)
		{
			if ((p[1] = ft_pipe(&info.fd)) == -1)
				return (1);
			p[0] = info.fd;
		}
		else
			dup2(f[1], 1);
		if (putcmd(cmds, i, info))
			return (1);
		i++;
	}
	ft_endcmds(cmds, f[0]);
	return (0);
}

int			ft_putcmds(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_putcmd(cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

static char		**creation(char **table)
{
	char	**new;

	g_pid = 0;
	new = ft_tabdup(table);
	return (new);
}

int				main(void)
{
	extern char		**environ;

	if (ft_tinit() == -1 || ft_checktitty())
		return (0);
	signal(SIGINT, ft_signal);
	signal(SIGWINCH, ft_winch);
	SAFE(g_environ = creation(environ));
	g_input_type = 0;
	ft_shell();
	ft_freetable(&g_environ);
	return (1);
}
