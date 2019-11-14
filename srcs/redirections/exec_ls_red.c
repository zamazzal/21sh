/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ls_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:25:56 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/14 18:25:58 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int	exec_on_ampersand(t_red *red, int *fd)
{
//	int		right_fd;
	int		left_fd;
	int		len;
	int		i;
	char	*buf;

	i = 0;
	while (red->right[i] == ' ')
		i++;
	red->right = red->right + i;
	len = ft_strlen(red->right);
	left_fd = red->left == NULL ? 0 : ft_atoi(red->left);
	if (redirect_ltor(left_fd, red->right, 0, fd) == -1)
		return (-1);
	else if (red->right[0] == '-')
		close(left_fd);
	else if (red->right[len - 1] == '-')
	{
		buf = ft_strsub(red->right, 0, len);
		return (redirect_ltor(left_fd, buf, 1, fd) == -1 ? -1 : ambiguous_red(red));
	}
	else
		ambiguous_red(red);
	return (0);
}

int     exec_ls_red(t_red *red, int *fd)
{
	int     right_fd;
	int     left_fd;
	int		i;

	if (red->right[0] != '&')
	{
		i = 0;
		while (red->right[i] == ' ')
			i++;
		red->right = red->right + i;
		if ((right_fd = open_file(red->right, O_RDONLY)) == -1)
			return (-1);
		left_fd = red->left == NULL ? 0 : ft_atoi(red->left);
		dup2(right_fd, left_fd);
		if (left_fd == 1)
			*fd = right_fd;
	}
	else
		return (exec_on_ampersand(red, fd));
	return (0);
}