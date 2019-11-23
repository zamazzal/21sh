/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:26:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/19 18:35:45 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		exec_rd_red(t_red *red, int *fd)
{
	char	*right_buf;
	int		right_fd;
	int		left_fd;

	right_buf = red->right;
	while (right_buf[0] == ' ')
		right_buf++;
	if (right_buf[0] == '&')
	{
		ft_puterror("syntax error near unexpected token `&'");
		return (-1);
	}
	if ((right_fd = open_file(right_buf, O_WRONLY | O_APPEND | O_CREAT)) == -1)
		return (-1);
	left_fd = red->left == NULL ? 1 : ft_atoi(red->left);
	dup2(right_fd, left_fd);
	if (left_fd == 1)
		*fd = right_fd;
	return (right_fd);
}
