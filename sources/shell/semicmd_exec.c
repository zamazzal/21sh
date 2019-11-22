/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicmd_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:40:30 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/22 15:15:03 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	ft_gotonext(int *i, t_to_close **toclose
, t_semiherdoc **semiherdoc, char *cmd)
{
	(*i)++;
	close_toclose(toclose);
	*toclose = NULL;
	*semiherdoc = (*semiherdoc)->next;
	ft_strdel(&cmd);
}

static void	ft_initputcmd(int *i, t_info *info
, t_to_close **toclose, char **cmds)
{
	*i = 0;
	(*info).fd = -1;
	(*info).mode = (ft_tablen(cmds) > 1) ? 1 : 0;
	*toclose = NULL;
}

static void	ft_lastpipe(int lfd, int rfd)
{
	if (lfd == -1)
		dup2(rfd, 1);
	else
		dup2(rfd, lfd);
}

static void	ft_firstcmd(int i, int fd)
{
	if (i > 0)
	{
		dup2(fd, 0);
		close(fd);
	}
}

int			ft_exec_cmd(char **cmds, t_fd fd, t_semiherdoc *semiherdoc)
{
	int			i;
	int			p[2];
	t_info		info;
	t_afterred	red;
	t_to_close	*toclose;

	ft_initputcmd(&i, &info, &toclose, cmds);
	while (cmds[i] != NULL)
	{
		if (ft_hdexec(semiherdoc->content) || ft_reds(cmds[i], &toclose, &red))
			return (0);
		ft_firstcmd(i, p[0]);
		if (cmds[i + 1] != NULL)
		{
			if ((p[1] = ft_pipe(&info.fd, red.fd, red.cmd)) == -1)
				return (0);
			p[0] = info.fd;
		}
		else
			ft_lastpipe(red.fd, fd.f[1]);
		if (putcmd(red.cmd, cmds, info, &toclose))
			return (1);
		ft_gotonext(&i, &toclose, &semiherdoc, red.cmd);
	}
	return (0);
}
