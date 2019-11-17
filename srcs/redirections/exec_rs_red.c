/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rs_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:57:17 by aihya             #+#    #+#             */
/*   Updated: 2019/11/17 18:54:57 by aihya            ###   ########.fr       */
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

int		redirect_ltor(int left_fd, char *buf, int close_right, int *fd)
{
	int		right_fd;

	right_fd = -2;
	
	if (ft_strisnum(buf))
	{
		if (test_fd(right_fd = ft_atoi(buf)) == -1)
			return (-1);
		dup2(right_fd, left_fd);
		if (left_fd == 1)
			*fd = right_fd;
		if (close_right)
			close(right_fd);
		return (-3);
	}
	return (right_fd);
}

int		redirect_to_file(t_red *red, int left_fd, char *buf, int *fd)
{
	int		right_fd;

	right_fd = open_file(buf, O_WRONLY|O_TRUNC|O_CREAT);
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

	right_buf = red->right;
	right_buf++;
	while (right_buf[0] == ' ')
		right_buf++;
	len = ft_strlen(right_buf);	
	left_fd = red->left == NULL ? 1 : ft_atoi(red->left);
	right_fd = redirect_ltor(left_fd, right_buf, 0, fd);
	if (right_fd == -1)
		return (-1);
	else if (right_fd == -3)
		return (0);
	else if (right_buf[0] == '-')
		close(left_fd);
	else if (right_buf[len - 1] == '-')
	{
		buf = ft_strsub(right_buf, 0, len-1);
		right_fd = redirect_ltor(left_fd, buf, 1, fd);
		if (right_fd == -2 || right_fd == -1)
			return (-1);
		else
			return (ambiguous_red(red));
	}
	else if ((right_fd = redirect_to_file(red, left_fd, right_buf, fd)) == -1)
		return (-1);
	return (right_fd);
}

int     exec_rs_red(t_red *red, int *fd)
{
	char	*right_buf;
	int     right_fd;
	int		left_fd;
	int		i;

	right_buf = red->right;
	if (right_buf[0] != '&')
	{
		i = 0;
		while (right_buf[i] == ' ')
			i++;
		right_buf = right_buf + i;
		if ((right_fd = open_file(red->right, O_WRONLY|O_TRUNC|O_CREAT)) == -1)
			return (-1);
		if (red->left && red->left[0] == '&')
		{
			dup2(right_fd, 1);
			*fd = right_fd;
			dup2(right_fd, 2);
		}
		else
		{
			left_fd = (red->left == NULL) ? 1 : ft_atoi(red->left);
	/*		if (test_fd(left_fd) == -1)
				return (-1);
	*/		dup2(right_fd, left_fd);
			if (left_fd == 1)
				*fd = right_fd;
		}
	}
	else
		right_fd = exec_on_ampersand(red, fd);
	return (right_fd);
}
