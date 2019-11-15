/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:01:43 by aihya             #+#    #+#             */
/*   Updated: 2019/11/14 17:23:08 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void	close_fd_buf(int **fd_buf)
{
	int		i;

	i = 0;
	while ((*fd_buf)[i] != -1)
	{
		close((*fd_buf)[i]);
		i++;
	}
	if (*fd_buf)
	{
		free(*fd_buf);
		*fd_buf = NULL;
	}
}

void	append_fd_buf(int **fd_buf, int fd)
{
	int		i;
	int		*new_buf;

	if (*fd_buf == NULL)
	{
		(*fd_buf) = (int *)malloc(sizeof(int));
		(*fd_buf)[0] = fd;
		return ;
	}
	i = 0;
	while ((*fd_buf)[i] != -1)
		i++;
	new_buf = (int *)malloc(sizeof(int) * (i + 1));
	while ((*fd_buf)[i] != -1)
	{
		new_buf[i] = (*fd_buf)[i];
		i++;
	}
	new_buf[i++] = fd;
	new_buf[i] = -1;
	free(*fd_buf);
	(*fd_buf) = new_buf;
}

t_afterred	exec_reds(char *cmd, int *status, int **fd_buf)
{
	t_red	*reds;
	t_red	*curr;
	t_afterred red;
	int		fd;

	red.fd = -1;
	red.cmd = cmd;
	reds = extract_reds(cmd);
	//ft_putendl("1");
	if (reds == NULL)
		return (red);
	clean_reds_wings(reds);
	red.cmd = get_clean_cmd(cmd, reds);
	if (!red.cmd)
		red.cmd = ft_strdup("cat");
	//ft_putendl("2");
	curr = reds;
	while (curr)
	{
		if (curr->type == RS)
		{
			if ((fd = exec_rs_red(curr, &red.fd)) == -1)
				*status = -1;
		}
		else if (curr->type == RD)
		{
			if ((fd = exec_rd_red(curr, &red.fd)) == -1)
				*status = -1;
		}
		else if (curr->type == LS)
		{
			if ((fd = exec_ls_red(curr, &red.fd)) == -1)
				*status = -1;
		}
		if (fd != -1)
		{
			append_fd_buf(fd_buf, fd);
		}
		if (*status == -1)
			break ;

		curr = curr->next;
	}
	//ft_putendl("3");
	if (*status != -1)
	{
		return (red);
	}
	ft_strdel(&red.cmd);
	return (red);
}
