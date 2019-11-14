/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rs_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:57:17 by aihya             #+#    #+#             */
/*   Updated: 2019/11/12 20:43:24 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		test_fd(int fd)
{
	if (read(fd, NULL, 0) == -1)
	{
		ft_putstr_fd("Bad file descriptor: ", 2);
		ft_putnbr_fd(fd, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (1);
}

int     open_file(char *path, int oflags)
{
	int     fd;
	struct stat	st;

	if (lstat(path, &st) == -1 && oflags == O_RDONLY)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	fd = open(path, oflags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (-1); 
	}
	return (fd);
}

int		ambiguous_red(t_red *red)
{
	ft_putstr_fd("ambiguous redirect: ", 2);
	print_red(red);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int		redirect_ltor(int left_fd, char *buf, int close_right)
{
	int		right_fd;

	right_fd = -1;
	if (ft_strisnum(buf))
	{
		if (test_fd(right_fd = ft_atoi(buf)) == -1)
			return (-1);
		dup2(right_fd, left_fd);
		if (close_right)
			close(right_fd);
	}
	return (right_fd);
}

int		redirect_to_file(t_red *red, int left_fd, char *buf)
{
	int		right_fd;

	right_fd = open_file(buf, O_WRONLY|O_TRUNC|O_CREAT);
	if (right_fd == -1)
		return (-1);
	if (left_fd != 1)
		return (ambiguous_red(red));
	dup2(right_fd, 1);
	dup2(right_fd, 2);
	return (right_fd);
}

static int	exec_on_ampersand(t_red *red)
{
	int		right_fd;
	int		left_fd;
	char	*buf;
	int		len;

	red->right++;
	while (red->right[0] == ' ')
		red->right++;
	len = ft_strlen(red->right);
	left_fd = red->left == NULL ? 1 : ft_atoi(red->left);
	if ((right_fd = redirect_ltor(left_fd, red->right, 0)) == -1)
		return (-1);
	else if (red->right[0] == '-')
		close(left_fd);
	else if (red->right[len - 1] == '-')
	{
		buf = ft_strsub(red->right, 0, len);
		if ((right_fd = redirect_ltor(left_fd, buf, 1)) == -1)
			return (-1);
		else
			return (ambiguous_red(red));
	}
	else if ((right_fd = redirect_to_file(red, left_fd, red->right)) == -1)
		return (-1);
	return (right_fd);
}

int     exec_rs_red(t_red *red)
{
	int     right_fd;
	int		left_fd;
	int		i;

	if (red->right[0] != '&')
	{
		i = 0;
		while (red->right[i] == ' ')
			i++;
		red->right = red->right + i;
		if ((right_fd = open_file(red->right, O_WRONLY|O_TRUNC|O_CREAT)) == -1)
			return (-1);
		if (red->left && red->left[0] == '&')
		{
			dup2(right_fd, 1);
			dup2(right_fd, 2);
		}
		else
		{
			left_fd = (red->left == NULL) ? 1 : ft_atoi(red->left);
	/*		if (test_fd(left_fd) == -1)
				return (-1);
	*/		dup2(right_fd, left_fd);
		}
	}
	else
		return (exec_on_ampersand(red));
	return (right_fd);
}
