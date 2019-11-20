/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:39:51 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:45:30 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static t_fd		ft_savefd(void)
{
	t_fd fd;

	fd.f[0] = dup(0);
	fd.f[1] = dup(1);
	fd.f[2] = dup(2);
	return (fd);
}

static void		ft_closefd(t_fd fd)
{
	close(fd.f[0]);
	close(fd.f[1]);
	close(fd.f[2]);
}

static void		ft_endcmds(char **cmds, t_fd fd)
{
	dup2(fd.f[1], 1);
	dup2(fd.f[2], 2);
	dup2(fd.f[0], 0);
	ft_waitpids();
	g_pid = 0;
	ft_freetable(&cmds);
	ft_closefd(fd);
}

static int		ft_putcmd(char *cmd, t_semiherdoc *semiherdoc)
{
	char **cmds;
	t_fd fd;

	if (!(cmds = ft_cmdsplit(cmd, '|')))
		return (1);
	fd = ft_savefd();
	if (ft_exec_cmd(cmds, fd, semiherdoc))
		return (1);
	ft_endcmds(cmds, fd);
	return (0);
}

int				ft_putcmds(char **cmd, char **history)
{
	int			i;
	t_herdoc	*herdoc;
	t_herdoc	*head;
	int			status;

	i = 0;
	status = 0;
	herdoc = ft_herdoc(cmd, history, &status);
	if (status)
		return (0);
	head = herdoc;
	while (cmd[i] != NULL)
	{
		if (ft_putcmd(cmd[i], head->semiherdoc))
		{
			ft_freeherdoc(herdoc);
			return (1);
		}
		i++;
		herdoc = head;
		head = head->next;
		free(herdoc);
	}
	free(head);
	return (0);
}
