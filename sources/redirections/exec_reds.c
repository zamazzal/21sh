/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 14:01:43 by aihya             #+#    #+#             */
/*   Updated: 2019/11/20 18:52:34 by zamazzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysh.h"

static char		*ft_nocmd(int type)
{
	if (type == RS || type == RD || type == LD)
		return (ft_strdup("cat"));
	if (type == LS)
		return (ft_strdup("more"));
	return (ft_strdup("cat"));
}

static void		free_reds(t_red **reds)
{
	t_red	*curr;
	t_red	*next;

	curr = *reds;
	while (curr)
	{
		next = curr->next;
		free(curr->left);
		free(curr->right);
		free(curr->o_left);
		free(curr->o_right);
		free(curr);
		curr = next;
	}
}

void			exec_red(t_red *red, int *aft_fd
, int *status, t_to_close **toclose)
{
	int		fd;

	fd = -1;
	if (red->type == RS)
	{
		if ((fd = exec_rs_red(red, aft_fd)) == -1)
			*status = -1;
	}
	else if (red->type == RD)
	{
		if ((fd = exec_rd_red(red, aft_fd)) == -1)
			*status = -1;
	}
	else if (red->type == LS)
	{
		if ((fd = exec_ls_red(red, aft_fd)) == -1)
			*status = -1;
	}
	if (fd > 0)
		append_toclose(toclose, fd);
}

t_afterred		exec_reds(char *cmd, int *status, t_to_close **toclose)
{
	t_red		*reds;
	t_red		*curr;
	t_afterred	red;

	red.fd = -1;
	red.cmd = ft_strdup(cmd);
	if (!(reds = extract_reds(cmd)))
		return (red);
	ft_strdel(&red.cmd);
	clean_reds_wings(reds);
	curr = reds;
	red.cmd = get_clean_cmd(cmd, reds);
	red.cmd = (!red.cmd) ? ft_nocmd(curr->type) : red.cmd;
	while (curr)
	{
		exec_red(curr, &red.fd, status, toclose);
		if (*status == -1)
			break ;
		curr = curr->next;
	}
	free_reds(&reds);
	if (*status != -1)
		return (red);
	ft_strdel(&red.cmd);
	return (red);
}
