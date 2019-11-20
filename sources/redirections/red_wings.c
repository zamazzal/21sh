/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_wings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:03:19 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 18:50:09 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	get_right_content(char *cmd, int *index, char **right)
{
	int		i;
	char	q;

	i = *index;
	while (cmd[i] && cmd[i] == ' ')
		ft_strappend(right, cmd[i++], 1);
	while (cmd[i] && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(right, cmd[i++], 1);
		if (cmd[i - 1] && ft_strchr("\"\'", cmd[i - 1]))
		{
			q = cmd[i - 1];
			while (cmd[i] != q)
				ft_strappend(right, cmd[i++], 1);
			ft_strappend(right, cmd[i++], 1);
		}
	}
	*index = i;
}

static char	*get_right(char *cmd, int pos, int steps)
{
	int		i;
	char	*right;
	char	q;

	right = NULL;
	i = pos + steps;
	get_right_content(cmd, &i, &right);
	if (ft_strlen(right) == 1 && right[0] == '&')
	{
		while (cmd[i] && cmd[i] == ' ')
			ft_strappend(&right, cmd[i++], 1);
		while (cmd[i] && !ft_strchr("> <", cmd[i]))
		{
			ft_strappend(&right, cmd[i++], 1);
			if (ft_strchr("\"\'", cmd[i - 1]))
			{
				q = cmd[i - 1];
				while (cmd[i] != q)
					ft_strappend(&right, cmd[i++], 1);
				ft_strappend(&right, cmd[i++], 1);
			}
		}
	}
	return (right);
}

static void	free_left(char **left)
{
	char	*tmp;

	if (*left == NULL)
	{
		tmp = ft_strrev(*left);
		ft_strdel(left);
		*left = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

static char	*get_left(char *cmd, int pos)
{
	int		i;
	char	*left;
	char	q;

	left = NULL;
	i = pos - 1;
	while (i >= 0 && cmd[i] == ' ')
		ft_strappend(&left, cmd[i--], 1);
	while (i >= 0 && !ft_strchr("> <", cmd[i]))
	{
		ft_strappend(&left, cmd[i--], 1);
		if (ft_strchr("\"\'", cmd[i + 1]))
		{
			q = cmd[i + 1];
			while (cmd[i] != q)
				ft_strappend(&left, cmd[i--], 1);
			ft_strappend(&left, cmd[i--], 1);
		}
	}
	free_left(&left);
	return (left);
}

char		**get_red_wings(char *cmd, t_pos_tab *node)
{
	char **wings;

	wings = (char **)malloc(sizeof(char *) * 3);
	if (node->type == LS || node->type == RS)
	{
		wings[0] = get_right(cmd, node->pos, 1);
		wings[1] = get_left(cmd, node->pos);
	}
	else if (node->type == LD || node->type == RD)
	{
		wings[0] = get_right(cmd, node->pos, 2);
		wings[1] = get_left(cmd, node->pos);
	}
	wings[2] = NULL;
	return (wings);
}
