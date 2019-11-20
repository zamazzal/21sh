/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_reds_wings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:21:17 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 18:50:59 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static void	clean_right(char **right)
{
	char	*tmp;
	int		vc;

	vc = valid_right_chars(*right);
	tmp = ft_strsub(*right, 0, vc);
	if (*right)
		free(*right);
	*right = tmp;
}

static void	clean_left(char **left, int type)
{
	char	*tmp;
	int		vc;

	vc = valid_left_chars(*left, type);
	tmp = ft_strsub(*left, ft_strlen(*left) - vc, vc);
	if (*left)
		free(*left);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		*left = NULL;
	}
	else
		*left = tmp;
}

int			open_file(char *path, int oflags)
{
	int			fd;
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

static void	expand_wing(char **a_wing)
{
	char	*tmp;

	tmp = ft_strdup(*a_wing);
	free(*a_wing);
	*a_wing = ms_expand_arg(tmp);
	free(tmp);
}

void		clean_reds_wings(t_red *reds)
{
	t_red	*red;

	red = reds;
	while (red)
	{
		red->o_left = ft_strdup(red->left);
		red->o_right = ft_strdup(red->right);
		clean_left(&(red->left), red->type);
		if (red->left != NULL)
			expand_wing(&(red->left));
		clean_right(&(red->right));
		if (red->right != NULL)
			expand_wing(&(red->right));
		red = red->next;
	}
}
