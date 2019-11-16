/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rd_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:26:06 by zamazzal          #+#    #+#             */
/*   Updated: 2019/11/14 18:26:07 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int     exec_rd_red(t_red *red, int *fd)
{
	int     right_fd;
	int     left_fd;

	while (red->right[0] == ' ')
		red->right++;
	if (red->right[0] == '&')
	{
		ft_puterror("syntax error near unexpected token `&'");
		return (-1);
	}
	if ((right_fd = open_file(red->right, O_WRONLY|O_APPEND|O_CREAT)) == -1)
		return (-1);
	left_fd = red->left == NULL ? 1 : ft_atoi(red->left);
	dup2(right_fd, left_fd);
	if (left_fd == 1)
		*fd = right_fd;
	return (right_fd);
}