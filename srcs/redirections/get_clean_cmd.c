/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:35:13 by aihya             #+#    #+#             */
/*   Updated: 2019/11/11 17:06:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

int		is_clean(char *str)
{
	int		i;
	int		clean;

	i = 0;
	clean = 1;
	while (str[i])
	{
		if (str[i] != 32 && !(clean = 0))
			break;
		i++;
	}
	return (clean);
}

int		valid_left_chars(char *left, int type)
{
	int		len;

	if (left == NULL)
		return (0);
	len = ft_strlen(left);
	if ((len > 0 && left[len - 1] == 32) || is_clean(left))
		return (0);
	if (ft_strisnum(left))
		return (len);
	else if (left[len - 1] == '&' && type != RD && type != LS)
		return (1);
	return (0);
}

int		valid_right_chars(char *right)
{
	int		amp;
	int		len;
	int		i;

	if (is_clean(right))
		return (0);
	len = ft_strlen(right);
	i = 0;
	amp = 0;
	if (right[0] == '&' && (amp = 1))
		i++;
	if (is_clean(right + i))
		return (i);
	while (right[i] && right[i] == ' ')
		i++;
	while (right[i] && right[i] != ' ')
	{
		if (amp && right[i] == '-' && ++i)
			break ;
		i++;
	}
	return (i);
}

char	*get_clean_cmd(char *cmd, t_red *reds)
{
	t_red	*red;
	char	*clean_cmd;
	int		i;
	int		n;

	red = reds;
	clean_cmd = NULL;
	i = 0;
	while (red)
	{
		n = ft_strlen(red->left);
		while (i < red->pos - n)
		{
			ft_strappend(&clean_cmd, cmd[i], 1);
			i++;
		}
		i = ((red->type == LS || red->type == RS) ? i + 1 : i + 2) + n;
		i += ft_strlen(red->right);
		red = red->next;
	}
	while (cmd[i])
	{
		ft_strappend(&clean_cmd, cmd[i], 1);
		i++;
	}
	return (clean_cmd);
}
