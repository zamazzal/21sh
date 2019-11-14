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

int			putcmd(char *cmd, char **cmds, t_info info)
{
	char **argv;

	argv = ms_parse(cmd);
	if (!(ft_builtins(ctables(argv), info)))
	{
		ft_freetable(&cmds);
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

int		ft_pipe(int *fd, int f)
{
	int p[2];

	if (pipe(p) == -1)
		return (-1);
	*fd = p[0];
	if (f != -1)
		dup2(p[1], f);
	else
		dup2(p[1], 1);
	close(p[1]);
	return (p[1]);
}

void			ft_backline()
{
	int x;

	x = ft_getcurpos2();
	if (x > 1)
	{
		ft_putterm("mr");
		ft_putchar('%');
		ft_putterm("me");
		ft_putchar(' ');
		ft_putchar('\n');
	}
}

void			ft_waitpids(void)
{
	int r;
	int x;

	r = wait(NULL);
	x = 0;
	while (r > 0)
	{
		x++;
		r = wait(NULL);
	}
	if (x)
		ft_backline();
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
	int f[3];
	int p[2];
	t_info	info;
	t_afterred	red;
	int		status;
	int		*fd_buf;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return (1);
	i = 0;
	f[0] = dup(0);
	f[1] = dup(1);
	f[2] = dup(2);
	info.fd = -1;
	info.mode = (ft_tablen(cmds) > 1) ? 1 : 0;
	fd_buf = NULL;
	while (cmds[i] != NULL)
	{
		//ft_putendl("xxxxx0xxxxxxx");
		// add a parameter to help close opened file descriptors
		append_fd_buf(&fd_buf, -1);
		status = 0;
		//ft_putendl("xxxxx1xxxxxxx");
		///////////////// * Redirections * /////////////////
		red = exec_reds(cmds[i], &status, &fd_buf);
		if (red.cmd == NULL)
		{
			if (status == -1 && !(status = 0))
			{
				close_fd_buf(&fd_buf);
				break ;
			}
		}
		//ft_putendl("xxxxxxx2xxxxxx");
		///////////////// * PIPE * /////////////////
		if (i > 0)
			ft_inputdone(p[0]);
		if (cmds[i + 1] != NULL)
		{
			if ((p[1] = ft_pipe(&info.fd, red.fd)) == -1)
				return (1);
			p[0] = info.fd;
		}
		else
		{
			if (red.fd == -1)
				dup2(f[1], 1);
			else
				dup2(f[1], red.fd);
		}
		//ft_putendl("xxxxxxx3xxxxxx");
		///////////////// * PARSE & PUTCMD * /////////////////
		if (putcmd(red.cmd, cmds, info))
			return (1);
		//ft_putendl("xxxxxx4xxxxxxx");
		close_fd_buf(&fd_buf);
		i++;
	}
	dup2(f[1], 1);
	dup2(f[2], 2);
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
void			ft_cpy()
{
	g_cpy.p1 = -1;
	g_cpy.p2 = -1;
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
