/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rs_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:57:17 by aihya             #+#    #+#             */
/*   Updated: 2019/11/22 15:04:21 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	redirect_to_file(t_red *red, int left_fd, char *buf, int *fd)
{
	int		right_fd;

	right_fd = open_file(buf, O_WRONLY | O_TRUNC | O_CREAT);
	if (right_fd == -1)
		return (-1);
	if (left_fd != 1)
		return (ambiguous_red(red));
	dup2(right_fd, 1);
	*fd = right_fd;
	dup2(right_fd, 2);
	return (right_fd);
}

static int	exec_on_ampersand(t_red *red, int *fd)
{
	char	*right_buf;
	int		right_fd;
	int		left_fd;
	char	*buf;
	int		len;

	right_buf = prep_amp(red, &len, &left_fd);
	if ((right_fd = redirect_ltor(left_fd, right_buf, 0, fd)) == -1)
		return (-1);
	else if (right_fd == -3)
		return (0);
	else if (right_buf[0] == '-')
		close(left_fd);
	else if (right_buf[len - 1] == '-')
	{
		buf = ft_strsub(right_buf, 0, len - 1);
		right_fd = redirect_ltor(left_fd, buf, 1, fd);
		if (right_fd == -3 || right_fd == -1)
			return (-1);
		else
			return (ambiguous_red(red));
	}
	else if ((right_fd = redirect_to_file(red, left_fd, right_buf, fd)) == -1)
		return (-1);
	return (right_fd);
}

static void	redirect_out_err(int right_fd, int *fd)
{
	dup2(right_fd, 1);
	*fd = right_fd;
	dup2(right_fd, 2);
}

int			exec_rs_red(t_red *red, int *fd)
{
	char	*right_buf;
	int		right_fd;
	int		left_fd;
	int		access;

	access = O_WRONLY | O_TRUNC | O_CREAT;
	right_buf = red->right;
	if (right_buf[0] != '&')
	{
		escape_spaces(&right_buf);
		if ((right_fd = open_file(right_buf, access)) == -1)
			return (-1);
		if (red->left && red->left[0] == '&')
			redirect_out_err(right_fd, fd);
		else
		{
			left_fd = (red->left == NULL) ? 1 : ft_atoi(red->left);
			dup2(right_fd, left_fd);
			*fd = left_fd == 1 ? right_fd : *fd;
		}
	}
	else
		right_fd = exec_on_ampersand(red, fd);
	return (right_fd);
}
