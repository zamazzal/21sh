/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:40:59 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/20 21:46:57 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

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

int		ft_hdexec(char **heredoc)
{
	int p[2];
	int i;

	i = 0;
	if (!heredoc)
		return (0);
	if (pipe(p) == -1)
		return (1);
	dup2(p[0], 0);
	close(p[0]);
	while (heredoc[i] != NULL)
	{
		ft_putendl_fd(heredoc[i], p[1]);
		i++;
	}
	ft_freetable(&heredoc);
	close(p[1]);
	return (0);
}

int		ft_reds(char *cmd, t_to_close **toclose, t_afterred *red)
{
	int		status;

	status = 0;
	*red = exec_reds(cmd, &status, toclose);
	if (!(*red).cmd)
	{
		if (status == -1 && !(status = 0))
		{
			close_toclose(toclose);
			return (1);
		}
	}
	return (0);
}
