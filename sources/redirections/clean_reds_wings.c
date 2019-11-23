/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_reds_wings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:21:17 by aihya             #+#    #+#             */
/*   Updated: 2019/11/22 17:03:11 by zamazzal         ###   ########.fr       */
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
	{
		free(*right);
		*right = NULL;
	}
	*right = tmp;
}

static void	clean_left(char **left, int type)
{
	char	*tmp;
	int		vc;

	vc = valid_left_chars(*left, type);
	tmp = ft_strsub(*left, ft_strlen(*left) - vc, vc);
	if (*left)
	{
		free(*left);
		*left = NULL;
	}
	if (ft_strlen(tmp) == 0)
	{
		ft_strdel(&tmp);
		*left = NULL;
	}
	else
		*left = tmp;
}

static void	expand_wing(char **a_wing)
{
	char	*tmp;

	tmp = ft_strdup(*a_wing);
	free(*a_wing);
	*a_wing = NULL;
	*a_wing = ms_expand_arg(tmp);
	ft_strdel(&tmp);
}

static int	invalidempty(t_red *red, t_red *reds, int *status)
{
	ambiguous_red(red);
	free_reds(&reds);
	*status = -1;
	return (0);
}

int			clean_reds_wings(t_red *reds, int *status)
{
	t_red	*red;
	char	*tmp;

	red = reds;
	while (red)
	{
		tmp = ft_strdup(red->left);
		red->o_left = ft_strrev(tmp);
		ft_strdel(&tmp);
		red->o_right = ft_strdup(red->right);
		clean_left(&(red->left), red->type);
		if (red->left != NULL)
			expand_wing(&(red->left));
		clean_right(&(red->right));
		if (red->right != NULL)
			expand_wing(&(red->right));
		if (red->right[0] == '&' && is_empty(red->right + 1))
			return (invalidempty(red, reds, status));
		red = red->next;
	}
	return (1);
}
