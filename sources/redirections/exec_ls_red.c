/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ls_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:25:56 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/22 15:04:05 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

void		escape_spaces(char **right_buf)
{
	while ((*right_buf)[0] == ' ')
		(*right_buf)++;
}

char		*prep_amp(t_red *red, int *len, int *left_fd)
{
	char	*right_buf;

	right_buf = red->right + 1;
	escape_spaces(&right_buf);
	*len = ft_strlen(right_buf);
	if (red->type == RS)
		*left_fd = red->left == NULL ? 1 : ft_atoi(red->left);
	else
		*left_fd = red->left == NULL ? 0 : ft_atoi(red->left);
	return (right_buf);
}

static int	exec_on_ampersand(t_red *red, int *fd)
{
	char	*right_buf;
	int		right_fd;
	int		left_fd;
	int		len;
	char	*buf;

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
		*fd = left_fd;
		if (right_fd == -2 || right_fd == -1)
			return (-1);
	}
	else
		return (ambiguous_red(red));
	return (right_fd);
}

int			exec_ls_red(t_red *red, int *fd)
{
	char	*right_buf;
	int		right_fd;
	int		left_fd;

	right_buf = red->right;
	if (right_buf[0] != '&')
	{
		while (right_buf[0] == ' ')
			right_buf++;
		if ((right_fd = open_file(right_buf, O_RDONLY)) == -1)
			return (-1);
		left_fd = red->left == NULL ? 0 : ft_atoi(red->left);
		dup2(right_fd, left_fd);
		if (left_fd == 1)
			*fd = right_fd;
	}
	else
		right_fd = exec_on_ampersand(red, fd);
	return (right_fd);
}
