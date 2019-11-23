/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:51:09 by aihya             #+#    #+#             */
/*   Updated: 2019/11/22 15:24:44 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static int			test_fd(int fd)
{
	if (read(fd, NULL, 0) == -1 && write(fd, NULL, 0) == -1)
	{
		ft_putstr_fd("Bad file descriptor: ", 2);
		ft_putnbr_fd(fd, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (1);
}

static void			print_red(t_red *red)
{
	ft_putstr_fd(red->o_left, 2);
	if (red->type == RS)
		ft_putstr_fd(">", 2);
	else if (red->type == LS)
		ft_putstr_fd("<", 2);
	else if (red->type == RD)
		ft_putstr_fd(">>", 2);
	else if (red->type == LD)
		ft_putstr_fd("<<", 2);
	ft_putstr_fd(red->o_right, 2);
}

int					ambiguous_red(t_red *red)
{
	ft_putstr_fd("ambiguous redirect: ", 2);
	print_red(red);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int					redirect_ltor(int left_fd, char *buf
, int close_right, int *fd)
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
